mod sm3;
mod sm2;

fn main() {
    let (sk, pk) = sm2::gen_keypair(); // 生成密钥对
    let enc_ctx = sm2::Encrypt::new(&pk); // 使用公钥创建加密上下文
    let enc = enc_ctx.encrypt(b"abc"); // 加密数据
    let dec_ctx = sm2::Decrypt::new(&sk); // 使用私钥创建解密上下文
    let dec = dec_ctx.decrypt(&enc); // 解密数据
    assert_eq!(String::from_utf8(dec).unwrap(), "abc"); // 断言解密后的数据与原文
    let (sk, pk) = sm2::gen_keypair(); // 生成密钥对
    let sign_ctx = sm2::Sign::new(&sk); // 使用私钥创建签名上下文
    let sign = sign_ctx.sign(b"abc"); // 签名数据
    let verify_ctx = sm2::Verify::new(&pk); // 使用公钥创建验证上下文
    let verify = verify_ctx.verify(b"abc", &sign); // 验证签名
    assert_eq!(verify, true); // 断言签名验证成功
    // 第一步：双方生成密钥对和临时密钥对
    let ida = b"id_a@company.com";
    let (ska, _) = sm2::gen_keypair();
    let keyexchange_a = sm2::KeyExchange::new(ida, &ska);
    let (a2b, rska) = keyexchange_a.keyexchange_1ab(16);

    let idb = b"id_b@company.com";
    let (skb, _) = sm2::gen_keypair();
    let keyexchange_b = sm2::KeyExchange::new(idb, &skb);
    let (b2a, rskb) = keyexchange_b.keyexchange_1ab(16);

// 第二步：双方使用对方的临时公钥和自己的临时私钥计算共享密钥
    let ka = keyexchange_a.keyexchange_2a(&rska, &b2a);
    let kb = keyexchange_b.keyexchange_2b(&rskb, &a2b);

// 第三步：验证共享密钥是否一致
    assert_eq!(ka.k, kb.k); // 断言共享密钥相同
    assert_eq!(ka.s12, kb.s12); // 断言其他交换信息一致
    println!("ALL IS OK!!!");
}