use std::env::args;
use std::fs::File;
use smcrypto::sm3;
use smcrypto::sm2;
use smcrypto::sm2::{keypair_from_pem_file, keypair_to_pem_file, pubkey_from_pem_file, pubkey_to_pem_file};
use smcrypto::sm4;
use std::io;
use std::io::Read;

fn usage() {
    //生成数字信封 要生成的明文和对方的公钥、共享密钥和IV
    //生成三个文件
    println!("Usage: -e -in <filename> -pub <publickey> -my <privatekey> -key <key> -iv <iv>");
    println!("Usage: -d -in <filename> -my <privatekey> -pub <publickey> -iv <iv>");
    //验证数字信封 假设当前目录下存在三个文件（同名不同后缀）、对方的公钥、自己的SM2密钥对、共享密钥和IV
}
fn read_file_to_bytes(path: &str) -> io::Result<Vec<u8>> {
    let mut file = File::open(path)?;
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer)?;
    Ok(buffer) // 直接返回 Vec<u8>
}

fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() == 2{
        if args[1] == "-key"{
            let (sk, pk) = sm2::gen_keypair();
            keypair_to_pem_file(&*sk, "mykey.pem");
            pubkey_to_pem_file(&*pk, "mypub.pem");
            // let (sk, pk) = sm2::gen_keypair();
            // let sign_ctx = sm2::Sign::new(&sk);
            // let sign = sign_ctx.sign(b"abc");
            // let verify_ctx = sm2::Verify::new(&pk);
            // let verify = verify_ctx.verify(b"abc", &sign);
        }else {
            usage();
        }
        return
    }
    if args.len() < 10 {
        usage();
        return;
    }
    if args[1] == "-e"{
        if args.len() < 12{
            usage();
            return;
        }
        if args[2] != "-in" || args[4] != "-pub" || args[6] != "-my" || args[8] != "-key" || args[10] != "-iv"{
            usage();
            return;
        }
        let iv = read_file_to_bytes(&*args[11]).expect("Error reading iv");
        let key = read_file_to_bytes(&*args[9]).expect("Error reading key");
        let yourpub =  sm2::pubkey_from_pem_file(&args[5]);
        let (sk, pk) = keypair_from_pem_file(&*args[7]);
        let sm4_cbc = sm4::CryptSM4CBC::new(&*key, &*iv);
        sm4_cbc.encrypt_to_file(&*args[3], "alice.txt");
        let crypto = read_file_to_bytes("alice.txt").expect("Error reading");
        let ctx = sm2::Encrypt::new(&*yourpub);
        ctx.encrypt_to_file(&*key, "alice.bin");
        let sig_ctx = sm2::Sign::new(&*sk);
        sig_ctx.sign_to_file(&*crypto, "alice.sig");
        println!("Success!");
    }else if args[1] == "-d" {
        if args[2] != "-in" || args[4] != "-my" || args[6] != "-pub" || args[8] != "-iv"{
            usage();
            return;
        }
        let txt = format!("{}.txt", args[3]);
        let sig = format!("{}.sig", args[3]);
        let keyc = format!("{}.bin", args[3]);
        let yourpub = pubkey_from_pem_file(&*args[7]);
        let (sk, pk) = keypair_from_pem_file(&*args[5]);
        let ver_ctx = sm2::Verify::new(&*yourpub);
        let data = read_file_to_bytes(&*txt).expect("Error to read data");
        let iv = read_file_to_bytes(&*args[9]).expect("Error reading iv");
        if !ver_ctx.verify_from_file(&*data, &*sig){
            println!("Verify error!");
            return;
        }
        let dec_ctx = sm2::Decrypt::new(&*sk);
        let key = dec_ctx.decrypt_from_file(&*keyc);
        let sm4_ctx = sm4::CryptSM4CBC::new(&*key, &*iv);
        sm4_ctx.decrypt_from_file(&*txt, "decrypt.txt");
    }else{
        usage();
    }
}
