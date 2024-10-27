use std::mem::transmute;

const SM3_LEN: usize = 256;
const SM3_T1: u32 = 0x79CC4519;
const SM3_T2: u32 = 0x7A879D8A;
const SM3_IVA: u32 = 0x7380166f;
const SM3_IVB: u32 = 0x4914b2b9;
const SM3_IVC: u32 = 0x172442d7;
const SM3_IVD: u32 = 0xda8a0600;
const SM3_IVE: u32 = 0xa96f30bc;
const SM3_IVF: u32 = 0x163138aa;
const SM3_IVG: u32 = 0xe38dee4d;
const SM3_IVH: u32 = 0xb0fb0e4e;

#[derive(Clone)]
struct Sm3State {
    state: [u32; 8],
    length: u64,
    curlen: usize,
    buf: [u8; 64],
}

impl Sm3State {
    fn new() -> Self {
        Self {
            state: [SM3_IVA, SM3_IVB, SM3_IVC, SM3_IVD, SM3_IVE, SM3_IVF, SM3_IVG, SM3_IVH],
            length: 0,
            curlen: 0,
            buf: [0u8; 64],
        }
    }

    fn p1(x: u32) -> u32 {
        x ^ Sm3State::rotl(x, 15) ^ Sm3State::rotl(x, 23)
    }

    fn p0(x: u32) -> u32 {
        x ^ Sm3State::rotl(x, 9) ^ Sm3State::rotl(x, 17)
    }

    fn ff0(a: u32, b: u32, c: u32) -> u32 {
        a ^ b ^ c
    }

    fn ff1(a: u32, b: u32, c: u32) -> u32 {
        (a & b) | (a & c) | (b & c)
    }

    fn gg0(e: u32, f: u32, g: u32) -> u32 {
        e ^ f ^ g
    }

    fn gg1(e: u32, f: u32, g: u32) -> u32 {
        (e & f) | (!e & g)
    }

    fn rotl(x: u32, n: u32) -> u32 {
        (x << n) | (x >> (32 - n))
    }

    fn big_endian(src: &[u8], bytelen: usize, des: &mut [u8]) {
        for i in 0..(bytelen / 4) {
            des[4 * i] = src[4 * i + 3];
            des[4 * i + 1] = src[4 * i + 2];
            des[4 * i + 2] = src[4 * i + 1];
            des[4 * i + 3] = src[4 * i];
        }
    }

    fn bi_to_w(bi: &[u32; 16], w: &mut [u32; 68]) {
        w[0..16].copy_from_slice(bi);
        for i in 16..68 {
            let tmp = w[i - 16] ^ w[i - 9] ^ Sm3State::rotl(w[i - 3], 15);
            w[i] = Sm3State::p1(tmp) ^ Sm3State::rotl(w[i - 13], 7) ^ w[i - 6];
        }
    }

    fn w_to_w1(w: &[u32; 68], w1: &mut [u32; 64]) {
        for i in 0..64 {
            w1[i] = w[i] ^ w[i + 4];
        }
    }

    fn cf(w: &[u32; 68], w1: &[u32; 64], v: &mut [u32; 8]) {
        let mut a = v[0];
        let mut b = v[1];
        let mut c = v[2];
        let mut d = v[3];
        let mut e = v[4];
        let mut f = v[5];
        let mut g = v[6];
        let mut h = v[7];
        let mut t = SM3_T1;

        for j in 0..64 {
            if j == 16 {
                t = Sm3State::rotl(SM3_T2, 16);
            } else if j > 0 {
                t = Sm3State::rotl(t, 1);
            }
            let ss1 = Sm3State::rotl(Sm3State::rotl(a, 12).wrapping_add(e).wrapping_add(t), 7);
            let ss2 = ss1 ^ Sm3State::rotl(a, 12);
            let tt1 = if j <= 15 {
                Sm3State::ff0(a, b, c)
            } else {
                Sm3State::ff1(a, b, c)
            }
                .wrapping_add(d)
                .wrapping_add(ss2)
                .wrapping_add(w1[j]);
            let tt2 = if j <= 15 {
                Sm3State::gg0(e, f, g)
            } else {
                Sm3State::gg1(e, f, g)
            }
                .wrapping_add(h)
                .wrapping_add(ss1)
                .wrapping_add(w[j]);

            d = c;
            c = Sm3State::rotl(b, 9);
            b = a;
            a = tt1;
            h = g;
            g = Sm3State::rotl(f, 19);
            f = e;
            e = Sm3State::p0(tt2);
        }

        v[0] ^= a;
        v[1] ^= b;
        v[2] ^= c;
        v[3] ^= d;
        v[4] ^= e;
        v[5] ^= f;
        v[6] ^= g;
        v[7] ^= h;
    }

    fn compress(&mut self) {
        let mut w = [0u32; 68];
        let mut w1 = [0u32; 64];
        let mut buf = [0u32; 16];

        for i in 0..16 {
            buf[i] = u32::from_be_bytes([self.buf[4 * i], self.buf[4 * i + 1], self.buf[4 * i + 2], self.buf[4 * i + 3]]);
        }

        Sm3State::bi_to_w(&buf, &mut w);
        Sm3State::w_to_w1(&w, &mut w1);
        Sm3State::cf(&w, &w1, &mut self.state);
    }

    fn process(&mut self, buf: &[u8]) {
        for &b in buf {
            self.buf[self.curlen] = b;
            self.curlen += 1;

            if self.curlen == 64 {
                self.compress();
                self.length += 512;
                self.curlen = 0;
            }
        }
    }

    fn done(&mut self, hash: &mut [u8; 32]) {
        self.length += (self.curlen as u64) << 3;

        self.buf[self.curlen] = 0x80;
        self.curlen += 1;

        if self.curlen > 56 {
            self.buf[self.curlen..64].fill(0);
            self.compress();
            self.curlen = 0;
        }

        self.buf[self.curlen..56].fill(0);

        self.buf[56..64].copy_from_slice(&self.length.to_be_bytes());
        self.compress();

        for (i, &s) in self.state.iter().enumerate() {
            hash[i * 4..i * 4 + 4].copy_from_slice(&s.to_be_bytes());
        }
    }
}

fn sm3_256(buf: &[u8], hash: &mut [u8; 32]) {
    let mut state = Sm3State::new();
    state.process(buf);
    state.done(hash);
}

fn main() {
    let mut hash = [0u8; 32];
    sm3_256(b"abc", &mut hash);
    for byte in &hash {
        print!("{:02x}", byte);
    }
    println!();
}
