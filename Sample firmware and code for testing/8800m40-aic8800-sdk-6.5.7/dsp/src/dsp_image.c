/*
 * Copyright (C) 2018-2020 AICSemi Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "dma_api.h"
#include "reg_sysctrl.h"
#include "dbg.h"

const uint32_t dsp_image_table[] = {
0x0015fe00,
0x00100191,
0x001001ed,
0x00101709,
0x00101711,
0x00101719,
0x00101721,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x001001f7,
0x001001f9,
0x00000000,
0x001001fb,
0x001001fd,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001019cd,
0x00101a1d,
0x00101a6d,
0x001001ff,
0x00100fa9,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x00101fd9,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x00102271,
0x00102279,
0x00102281,
0x00102269,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x00102289,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x00101e81,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x00102169,
0x001001ff,
0x00102155,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x001001ff,
0x474d4946,
0x00103020,
0xffffffff,
0xffffffff,
0xf380480d,
0x490d8808,
0x4b0e4a0d,
0xbfbe429a,
0x0b04f851,
0x0b04f842,
0xf04fe7f8,
0x4a0a0100,
0x429a4b0a,
0xf842bfbc,
0xe7fa1b04,
0x47804808,
0x47804808,
0x47004808,
0x0015fe00,
0x00103004,
0x00140180,
0x0014019c,
0x001401a0,
0x00145650,
0x00101881,
0x001021fd,
0x00101825,
0xe7fee7fe,
0xe7fee7fe,
0xe7fee7fe,
0xe7fee7fe,
0xe7fee7fe,
0x4ff0e92d,
0xb095461d,
0xf8dd4690,
0xf815b078,
0x91032b01,
0x28004607,
0x8177f000,
0xf0002a00,
0x24008389,
0x4400e9cd,
0x94029e03,
0x46a246a1,
0x0320f1a2,
0xd85a2b58,
0xf013e8df,
0x0059012d,
0x00590059,
0x032e0059,
0x00590059,
0x00590059,
0x012d030f,
0x012d0059,
0x0059032c,
0x00590109,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x006e0059,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x006e0059,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x00590059,
0x0059006e,
0x00590059,
0x00590059,
0x00590059,
0x006e0059,
0x006e006e,
0x0059006e,
0x00590059,
0x006e0107,
0x00590059,
0x006e0107,
0x00590059,
0x0059006e,
0x006e0059,
0x006e0059,
0x00590059,
0xf1a2006e,
0x29080131,
0x80daf240,
0x48992100,
0x0acaeb00,
0xa001f81a,
0x0f07f1ba,
0x83bef200,
0xf00ae8df,
0x9145536d,
0x06788568,
0xe7ee2107,
0x0341f1a2,
0xf2002b37,
0xe8df81fd,
0x01fdf013,
0x01fb01fb,
0x01fb01fb,
0x01fb01fb,
0x01fb01fb,
0x01fb01fb,
0x024c01fb,
0x01fb01fb,
0x01fb01fb,
0x01fb01fb,
0x01fb01fb,
0x01fb01fb,
0x01fb0121,
0x01fb01fb,
0x01fb01fb,
0x01fb01fb,
0x01fd01fb,
0x01560121,
0x01fb0121,
0x01fb01fb,
0x019b01fb,
0x01fb01fb,
0x024c01fb,
0x01fb01fb,
0x01fb0121,
0x01f001fb,
0x012101fb,
0x01fb01fb,
0x2b100121,
0x80c2f200,
0xf003e8df,
0xc0c0c0c9,
0xc0c0c0c0,
0xd0c0c0c0,
0xc0c0d7c0,
0x230000b9,
0x93029300,
0x33fff04f,
0xf04f9301,
0xf8150a01,
0x2a002b01,
0xaf30f47f,
0xd0622e00,
0x703b2300,
0xb0154620,
0x8ff0e8bd,
0x93012300,
0x0a04f04f,
0xb12ee7ed,
0xbf9c45a0,
0x2b01f807,
0x36fff106,
0xf04f3401,
0xe7e20a00,
0xd07b2a68,
0xd03f2a6c,
0x48574956,
0x72a3f44f,
0xfbd6f000,
0x0a06f04f,
0x2a2ae7d5,
0x9b01d062,
0xeb033a30,
0xeb020383,
0x93010343,
0x0a05f04f,
0x2a2ae7c9,
0x9b02d05c,
0xeb033a30,
0xeb020383,
0x93020343,
0x0a03f04f,
0x2106e7bd,
0x4b44e755,
0x0acaeb03,
0xa003f89a,
0x0f07f1ba,
0x8314f200,
0xf853a301,
0xbf00f02a,
0x001003eb,
0x001003b7,
0x00100517,
0x00100433,
0x001003e1,
0x0010041b,
0x00100401,
0x0010031d,
0xf0439b00,
0x93000302,
0x0a06f04f,
0x2105e797,
0x9b03e72f,
0xd09b2b00,
0xf8074620,
0xb0156c01,
0x8ff0e8bd,
0xeb01492c,
0xf89a0aca,
0xf1baa004,
0xf2000f07,
0xa10182e5,
0xf02af851,
0x001003eb,
0x001003b7,
0x0010039b,
0x00100437,
0x001003e1,
0x0010041b,
0x00100401,
0x0010031d,
0x3b04f85b,
0xf04f9301,
0xe76a0a05,
0x3b04f85b,
0xf04f9302,
0xe7640a03,
0xf0439b00,
0x93000301,
0x0a06f04f,
0x4614e75d,
0xf43f2a00,
0x9003af63,
0x9b00e685,
0x0340f043,
0xf04f9300,
0xe7500a02,
0x4810490f,
0x1213f240,
0xfb48f000,
0x0a02f04f,
0x9b00e747,
0x0310f043,
0xf04f9300,
0xe7400a02,
0xf0439b00,
0x93000308,
0x0a02f04f,
0x9b00e739,
0x0320f043,
0xf04f9300,
0xe7320a02,
0x001029a8,
0x0010292c,
0x0010294c,
0x079b9b00,
0x8194f100,
0x07d89b00,
0x8190f140,
0xf0002a64,
0xf85b8229,
0x3a581b04,
0x2a20b289,
0x821bf200,
0xf012e8df,
0x02190251,
0x02190219,
0x02190219,
0x02190219,
0x02190219,
0x02190245,
0x02190072,
0x02190219,
0x02190219,
0x02190219,
0x02190219,
0x02190219,
0x0219022d,
0x02190219,
0x00720219,
0x02190219,
0x9b020260,
0xf85b1e59,
0xf88d3b04,
0x9b003010,
0xf003aa04,
0x23010040,
0xd1702800,
0x06809800,
0x8115f140,
0xf0002b00,
0x461081e1,
0x0903eb02,
0x0e02eba4,
0x45e0e009,
0x7807d804,
0x7b01f802,
0x46173e01,
0x45483001,
0xeb00d007,
0x463a0c0e,
0xd1f02e00,
0x45483001,
0x4423d1f4,
0xf3402900,
0x18cc81c1,
0xe0082120,
0xd8034598,
0x1b01f802,
0x46173e01,
0x42a33301,
0x463ad005,
0xd1f32e00,
0x42a33301,
0xf04fd1f6,
0xe6b20a07,
0x07999b00,
0x9b00d403,
0xf10007da,
0xf85b81b3,
0x29001b04,
0x81b5f2c0,
0xa428f8df,
0xf10d2300,
0xfbaa0e50,
0xea4f2c01,
0xeb0c0cdc,
0xeba1008c,
0x46890040,
0xf1b93030,
0x46720f09,
0xf80e4661,
0x46180d01,
0x0301f103,
0x9900d8eb,
0xf1000609,
0x99008195,
0xf1400709,
0x1c8381d5,
0xf80e202b,
0x98000c01,
0xf0009902,
0x3a020040,
0x28001ac9,
0x2900d08e,
0x440cdd14,
0x0e30f04f,
0x45e0e008,
0xf800d803,
0x3e01eb01,
0x39014607,
0x80b0f000,
0x0c01eba4,
0x2e004638,
0x3901d1f1,
0x2100d1f5,
0xf47f2b00,
0x4691af7c,
0xf85be7a7,
0x2a002b04,
0x8123f040,
0x99029b00,
0x0040f003,
0xe7652300,
0xe7f7464a,
0x3b04f85b,
0xf8df9a02,
0x469ce37c,
0x3b01f81c,
0xf0002a00,
0x11198100,
0xf0032a15,
0xf81e030f,
0xf81e1001,
0xf88d3003,
0xbf281010,
0xeb022215,
0x3a010142,
0x3011f88d,
0x33fff101,
0x0101f1c1,
0xeb0cd01d,
0xf10d0a02,
0xf01c0213,
0xf81c0f03,
0xea4f0b01,
0xf0001920,
0xf81e000f,
0xf8829009,
0xf81e9000,
0x70500000,
0xf04fbf0c,
0xf04f093a,
0x45e2092e,
0x9c01f802,
0x0203f102,
0x9a00d1e5,
0x0240f002,
0xf0402a00,
0x98008157,
0x06809202,
0xf53faa04,
0x2b00af1f,
0xaf1ff47f,
0xf85be7a1,
0xf8df1b04,
0x468ce2e0,
0x093af04f,
0x3b06f81c,
0xf003111a,
0xf81e030f,
0xf81e2002,
0xf88d3003,
0xf88d3011,
0x31012010,
0xf811ab04,
0xf8832b01,
0x11109002,
0x020ff002,
0x0000f81e,
0x2002f81e,
0x458c70d8,
0xf103711a,
0xd1ee0303,
0xf1a39b02,
0x9b000111,
0xf003aa04,
0x23110040,
0x2900e6e4,
0xaf6cf77f,
0xf04f4421,
0xe0080c20,
0xd80345a0,
0xcb01f800,
0x46073e01,
0x42a13401,
0x4638d005,
0xd1f32e00,
0x42a13401,
0x460cd1f6,
0x2b002100,
0xaed3f47f,
0x2304e755,
0xeb01498e,
0xf81a0aca,
0xf1baa003,
0xf2000f07,
0xa301810d,
0xf02af853,
0x001003eb,
0x001003b7,
0x00100525,
0x00100433,
0x001003e1,
0x0010041b,
0x00100401,
0x0010031d,
0xe5302102,
0xe7df2301,
0xf85b3a58,
0x2a201b04,
0x808ff200,
0xf853a301,
0xbf00f022,
0x00100a37,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x00100a1f,
0x001009c7,
0x00100673,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009ef,
0x001009c7,
0x001009c7,
0x001009c7,
0x001009c7,
0x00100679,
0x001009c7,
0x001009c7,
0x00100a55,
0x46149e03,
0x111ae54a,
0x030ff003,
0x2002f81e,
0x3003f81e,
0x2010f88d,
0x3011f88d,
0x012ef06f,
0x220f232f,
0x7813e705,
0xf0002b00,
0x9b01808e,
0xf43f2b00,
0x9b01aed5,
0xf1c24611,
0x2b000001,
0x0c01eb00,
0xf811dd0f,
0x3b01ef01,
0x0f00f1be,
0x2b00d010,
0x9902d1f3,
0x93019800,
0x1ac94663,
0x0040f000,
0xeb00e628,
0xf8110c01,
0xf1beef01,
0xd1e40f00,
0x46639301,
0x98009902,
0xf0001ac9,
0xe6190040,
0xf04f461c,
0xe5020a07,
0x46914623,
0x9b00e634,
0xf0039902,
0xaa140040,
0xe60b2300,
0x1b04f85b,
0xe64ab209,
0x202d1c83,
0x9b00e66d,
0x0380f043,
0x93004249,
0x9b00e644,
0x0340f043,
0x23089300,
0x93022040,
0xc0acf8df,
0xf001aa14,
0x0909030f,
0x3003f81c,
0x3d01f802,
0xeba3ab14,
0xd1f40302,
0x1ac99902,
0xaa14e5e6,
0x0301f001,
0xf8023330,
0x08493d01,
0xeba3ab14,
0xd1f50302,
0xf8dfe7ba,
0xaa14e070,
0x030ff001,
0xf81e0909,
0xf8023003,
0xab143d01,
0x0302eba3,
0xe7abd1f4,
0xf0039b00,
0xe7cf0040,
0x92022200,
0xe5ccaa04,
0x06c99900,
0x9802d406,
0x98001ac1,
0xf0004672,
0xe5b90040,
0x20201c83,
0x9900e61f,
0x0040f001,
0xe5b19902,
0x48054904,
0x224af240,
0xf896f000,
0xbf00e497,
0x001029a8,
0x0010292c,
0x0010294c,
0xcccccccd,
0x00102994,
0x00102980,
0x4603b5f0,
0xf3efb0c3,
0x22008605,
0xa8029100,
0x7180f44f,
0xfb9cf7ff,
0xdd251e07,
0x681b4b19,
0xb326b353,
0x207eac02,
0xff6cf000,
0x230019e5,
0xf000e005,
0x42acff67,
0x3c01f814,
0xf814d010,
0x280a0b01,
0x2b0dd1f5,
0x200dd0f3,
0xff5af000,
0x0c01f814,
0xff56f000,
0xf81442ac,
0xd1ee3c01,
0x4b09b916,
0x601a2201,
0xb0434638,
0x4a06bdf0,
0x2b006813,
0xe7d5d0fc,
0xfef2f000,
0xd1d12e00,
0xbf00e7f5,
0x00145428,
0x40044040,
0xe92db40f,
0x4e1c43f0,
0xb0836873,
0x9c0ab1eb,
0x9068f8df,
0x8068f8df,
0x46201ca7,
0x5b01f814,
0x0366f105,
0xf1a50629,
0xb2db0280,
0x2d88d509,
0x6833d810,
0x40d343db,
0xd40607db,
0x462042a7,
0xa90bd1eb,
0xf7ff9101,
0xb003ff95,
0x43f0e8bd,
0x4770b004,
0xd8042b05,
0x3d9a6873,
0xd8ed42ab,
0xf240e7f3,
0x464922c2,
0xf0004640,
0x6873f80b,
0x42ab3d9a,
0xe7e8d8e2,
0x001455a4,
0x0010292c,
0x00102950,
0x4605b570,
0x4809460e,
0x46141611,
0xffb6f7ff,
0x4807b672,
0x437ff024,
0x46294632,
0xffaef7ff,
0x681b4b04,
0xd1fd2b00,
0xbf00bd70,
0x001029e8,
0x001029fc,
0x00140180,
0x4c06b510,
0x46202208,
0xf0012100,
0xf04ffe43,
0x230232ff,
0x2300e9c4,
0xbf00bd10,
0x001455a4,
0x4ff0e92d,
0x4c784877,
0xf7ffb089,
0x6823ff8b,
0xd0fc2b00,
0x46284d75,
0xfc06f000,
0x28004601,
0x8903d04b,
0x2040f8b5,
0x89439307,
0x88c78886,
0x3a019304,
0x93038983,
0x0008f105,
0x2040f8a5,
0x97069605,
0xfbb8f000,
0x9b072001,
0x463a6020,
0x46314867,
0xff66f7ff,
0xd0342e01,
0x68234c62,
0xd0fc2b00,
0xf0004863,
0x9905fbdf,
0x3044f8b5,
0x99068081,
0x4a6080c1,
0x81012100,
0x20013301,
0x7180f04f,
0x3044f8a5,
0x60116020,
0x68134a56,
0xd0fc2b00,
0x8310f3ef,
0x0401f013,
0xb672d100,
0x2001682b,
0xf000b163,
0xb904fae1,
0x4b4eb662,
0x601a2201,
0xe8bdb009,
0x23018ff0,
0xe7e56023,
0xfb06f000,
0x4a48e7f1,
0x2b006813,
0x9b04d0fc,
0x4c4a9a03,
0x9154f8df,
0xf8df4e49,
0xf013b158,
0xf0230f03,
0xf1080803,
0xf0220804,
0xbf080703,
0xf0124698,
0xf1070f03,
0xf04f0704,
0xbf080a01,
0xe0244617,
0xf8db6832,
0x483e1000,
0xa004f8a9,
0x42b91a89,
0x493cbf84,
0xf04f6809,
0xbf880300,
0xf8a91889,
0x443a3008,
0x60329b03,
0x2100bf98,
0x300af8a9,
0x100cf8c9,
0xfef4f7ff,
0x200cf8d9,
0x4b32b33a,
0x429c3410,
0x0910f109,
0x6832d02c,
0x1000f8db,
0xf8a4482e,
0x1a89a004,
0xbf844541,
0x68094929,
0x0300f04f,
0x1889bf88,
0xbf988123,
0x9b042100,
0x44428163,
0x603260e1,
0xfed2f7ff,
0x2a0068e2,
0x4923d1be,
0x22e44823,
0xff0cf7ff,
0x4920e7b8,
0x22eb4821,
0xff06f7ff,
0x34104b1b,
0xf109429c,
0xd1d20910,
0x481d2400,
0xfb00f000,
0x481c4912,
0x23089400,
0xf0002210,
0x481afb19,
0xfaf6f000,
0x22102308,
0x48194918,
0xf0009400,
0x4b05fb0f,
0x4042f8a5,
0xf8a52201,
0x601a4046,
0xbf00e73c,
0x00102a14,
0x4004405c,
0x0015fe00,
0x00102a28,
0x0015fe28,
0x40044100,
0x001401a0,
0x001452dc,
0x00102a94,
0x001452d8,
0x00140220,
0x00102a3c,
0x00102a50,
0x00102a70,
0x00102aa8,
0x0015fe10,
0x0015fe18,
0x0015fe30,
0x001452e0,
0x0015fe38,
0x001452d4,
0x4c15b530,
0x6823b083,
0xd0fc2b00,
0x460d2100,
0x48122248,
0xfd12f001,
0x48124911,
0x23049500,
0xf000222c,
0x4910fac9,
0x95004810,
0x222c2304,
0xfac2f000,
0x480f490e,
0x23089500,
0xf0002210,
0x490dfabb,
0x9500480d,
0x22102308,
0xfab4f000,
0x60232301,
0xbd30b003,
0x4004405c,
0x0015fe00,
0x00140220,
0x0015fe08,
0x00145360,
0x0015fe28,
0x001401a0,
0x0015fe18,
0x001452e0,
0x0015fe38,
0x4d27b570,
0xb104782c,
0x4826bd70,
0xfe2ef7ff,
0x4a264925,
0x48274b26,
0xf44f6008,
0x601141a0,
0xf7ff601c,
0xf000ffad,
0x4923f98d,
0xf0002001,
0x4922f991,
0xf0004620,
0x4b21f98d,
0x681a4c21,
0x49224821,
0x3240f422,
0x3280f442,
0x681a601a,
0x2240f422,
0x2280f442,
0x681a601a,
0x1240f422,
0x1280f442,
0x681a601a,
0x0240f422,
0x0280f442,
0xf04f601a,
0x60236370,
0x60034a15,
0xf44f26fc,
0xf8811480,
0x23016314,
0x702b600c,
0x48116813,
0x0380f043,
0x4070e8bd,
0xf7ff6013,
0xbf00bde7,
0x001402d0,
0x00102acc,
0x001452d8,
0x001452d4,
0x001452dc,
0x001402d4,
0x00100c19,
0x001010e9,
0x40044118,
0x40044108,
0x4004410c,
0xe000e100,
0x40044084,
0x00102adc,
0x681b4b10,
0x7080f013,
0x0199d10e,
0x015ad406,
0x4b0dd511,
0x6280f04f,
0x4770601a,
0xf04f4b0a,
0x601a7200,
0xb95af000,
0xf04f4b07,
0x601a7280,
0xf0002001,
0x011bb953,
0x4b03d503,
0x6200f04f,
0x4770601a,
0x4004411c,
0x40044108,
0xb9b2f000,
0xb4702300,
0x680d6804,
0xfbc4461e,
0x463436c5,
0x684e6845,
0x34c6fbc5,
0x688e6885,
0x34c6fbc5,
0x68ce68c5,
0x34c6fbc5,
0x690e6905,
0x34c6fbc5,
0x694e6945,
0x34c6fbc5,
0x698e6985,
0x34c6fbc5,
0x69ce69c5,
0x34c6fbc5,
0x6a0e6a05,
0x34c6fbc5,
0x6a4e6a45,
0x34c6fbc5,
0x6a8e6a85,
0x34c6fbc5,
0x6ace6ac5,
0x34c6fbc5,
0x6b0e6b05,
0x34c6fbc5,
0x6b4e6b45,
0x34c6fbc5,
0x6b8e6b85,
0x34c6fbc5,
0x6bce6bc5,
0x34c6fbc5,
0x6c0e6c05,
0x34c6fbc5,
0x6c4e6c45,
0x34c6fbc5,
0x6c8e6c85,
0x34c6fbc5,
0x6cce6cc5,
0x34c6fbc5,
0x6d0e6d05,
0x34c6fbc5,
0x6d4e6d45,
0x34c6fbc5,
0x6d8e6d85,
0x34c6fbc5,
0x6dce6dc5,
0x34c6fbc5,
0x6e0e6e05,
0x34c6fbc5,
0x6e4e6e45,
0x34c6fbc5,
0x6e8e6e85,
0x34c6fbc5,
0x6ecd6ec0,
0x34c5fbc0,
0x3400e9c2,
0x4770bc70,
0x4ff0e92d,
0x4c40483f,
0xf7ffb083,
0x6823fd23,
0xd0fc2b00,
0xf1064e3d,
0xf0000010,
0x4605f99d,
0xf8b6b1b8,
0x89037042,
0x888188c2,
0x3f014838,
0x7042f8a6,
0x60272701,
0xfd0cf7ff,
0x42bb88ab,
0x4c31d021,
0x2b006823,
0x4832d0fc,
0xf0004629,
0x2301f94b,
0x60234a2c,
0x2b006813,
0xf3efd0fc,
0xf0138310,
0xd1000401,
0x6930b672,
0xd0462800,
0xf0002000,
0xb904f893,
0x4b23b662,
0x601a2201,
0xe8bdb003,
0x4c208ff0,
0x2b006823,
0x4822d0fc,
0xf0004f1d,
0xf8d5f961,
0xf8d0900c,
0x4680a00c,
0x46522301,
0xf1096023,
0x46480170,
0xff30f7ff,
0x100cf8d8,
0xf7ff4819,
0xe9dafccd,
0xf9b9ab00,
0xf9b92070,
0x48161000,
0xab00e9cd,
0xfcc2f7ff,
0x88ea88ab,
0x3004f8a8,
0xf8a82308,
0xf8a82006,
0x683b3008,
0xd0fc2b00,
0x480e4641,
0xf8fcf000,
0x21014b0d,
0x7200f04f,
0x601a6039,
0xf000e7a1,
0xe7b8f87f,
0x00102aec,
0x4004405c,
0x0015fe00,
0x00102b00,
0x0015fe18,
0x0015fe38,
0x00102b14,
0x00102b2c,
0x0015fe30,
0x40044100,
0x220c4802,
0xf0012100,
0xbf00bb37,
0x00145410,
0xb5382801,
0x4604d808,
0xb189460d,
0xeb004810,
0x20000484,
0xbd386065,
0x480f4a0e,
0xf7ff2156,
0x490cfc7b,
0x2256480d,
0xfcb8f7ff,
0xbd382003,
0x48094a08,
0xf7ff2156,
0x4808fc6f,
0x22564905,
0xfcacf7ff,
0xeb004802,
0x20000484,
0xe7e26065,
0x00145410,
0x00102b50,
0x00102b70,
0x0010294c,
0xb5102801,
0xd9094604,
0x48134a12,
0xf7ff2166,
0x4910fc53,
0x22664811,
0xfc90f7ff,
0x8310f3ef,
0xd40407db,
0x2c01b672,
0xb662d90b,
0x2c01bd10,
0x4a0bd8fc,
0x68132001,
0xf404fa00,
0x60134323,
0x4b07bd10,
0x681a2001,
0xf404fa00,
0x601c4314,
0xe7ebb662,
0x00102b50,
0x00102b70,
0x0010294c,
0x00145410,
0xb5102801,
0xd9094604,
0x48144a13,
0xf7ff2175,
0x4911fc21,
0x22754812,
0xfc5ef7ff,
0x8310f3ef,
0xd40407db,
0x2c01b672,
0xb662d90c,
0x2c01bd10,
0x4a0cd8fc,
0x68132001,
0xf404fa00,
0x0304ea23,
0xbd106013,
0x20014a07,
0xfa006813,
0xea23f404,
0x60130304,
0xe7e9b662,
0x00102b50,
0x00102b70,
0x0010294c,
0x00145410,
0x68184b01,
0xbf004770,
0x00145410,
0x41f0e92d,
0x682c4d15,
0x4e15b334,
0xf8df4f15,
0xe0028058,
0x682c4798,
0xfab4b1f4,
0xf1c4f484,
0xb2e4041f,
0x46322c01,
0xf04f4638,
0xd90601ac,
0xfbd6f7ff,
0x463122ac,
0xf7ff4640,
0xeb05fc13,
0x68630484,
0xd1e52b00,
0x463122b5,
0xf7ff4640,
0x682cfc09,
0xd1e02c00,
0x81f0e8bd,
0x00145410,
0x00102b50,
0x00102b70,
0x0010294c,
0xe9c02300,
0x47703300,
0x4605b538,
0xb161460c,
0xb12b682b,
0x601c686b,
0x606c2300,
0xbd386023,
0x602c2300,
0x6023606c,
0x4903bd38,
0x22484803,
0xfbe2f7ff,
0xbf00e7ec,
0x00102b88,
0x00102ba8,
0x43f8e92d,
0xe9c02500,
0x9f085500,
0x4680b18b,
0x4616460c,
0x35014699,
0x46394632,
0xb10f4620,
0xf996f001,
0x46404621,
0xffcef7ff,
0x443445a9,
0xe8bdd1f1,
0xbf0083f8,
0xb1336803,
0x68196842,
0x429a6001,
0x2200bf04,
0x46186042,
0xbf004770,
0x41f0e92d,
0x4e734f72,
0x463db086,
0x46212400,
0x2b04f855,
0x34014630,
0xfb64f7ff,
0xd1f62c0d,
0x2111e9d7,
0x4d6c6c3b,
0xe9cd9300,
0x486b2101,
0xe9d76b79,
0xf7ff230e,
0x6829fb55,
0x68ab686a,
0x900068e8,
0xf7ff4866,
0x6a69fb4d,
0x6aeb6aaa,
0x6bec6b28,
0x0400e9cd,
0xf7ff4862,
0x6aacfb43,
0x01fff014,
0xf3c4d168,
0xf4142507,
0x46294f7f,
0x0c21d144,
0x6cfbd12e,
0xd523071c,
0xf7ff485a,
0x6d3bfb31,
0xd42107d8,
0xf7ff4858,
0x6cfbfb2b,
0xbf4c0759,
0x48574856,
0xfb24f7ff,
0xf3ef6d39,
0xf3ef8210,
0xf3ef8313,
0x90008011,
0xf7ff4852,
0x6cbcfb19,
0xd1712c00,
0x2c006c7c,
0xb006d156,
0x81f0e8bd,
0xf7ff484d,
0xe7ddfb0d,
0xf7ff484c,
0xe7dcfb09,
0x6340f3c4,
0x6000f3c4,
0x42c0f3c4,
0xf3c49303,
0xe9cd4380,
0x93002001,
0xf3c44845,
0xf3c44340,
0xf7ff4200,
0xe7bcfaf5,
0x33c0f3c4,
0x3000f3c4,
0x22c0f3c4,
0xf3c49304,
0xf3c43640,
0xe9cd2380,
0xe9cd3200,
0xf3c40602,
0x483a2340,
0x2200f3c4,
0xfadef7ff,
0xd5a2062d,
0x48374b2a,
0xf7ff6b99,
0xe79cfad7,
0x16c0f3c4,
0x1040f3c4,
0x1200f3c4,
0x03c0f3c4,
0x0602e9cd,
0x3200e9cd,
0xf3c4482f,
0xf0040340,
0xf7ff0201,
0x0626fac3,
0x6b69d581,
0xf7ff482b,
0xe77cfabd,
0x4f2b482a,
0xf0244e2b,
0xf7ff040f,
0xf504fab5,
0xe0067580,
0x1b04f854,
0xf7ff4630,
0x42a5faad,
0x0723d097,
0x4621d1f6,
0xf7ff4638,
0xe7f1faa5,
0xf8df4821,
0x4e1f807c,
0x040ff024,
0xfa9cf7ff,
0x7580f504,
0xf854e007,
0x46301b04,
0xfa94f7ff,
0xf43f42a5,
0x0722af7b,
0x4621d1f5,
0xf7ff4640,
0xe7f0fa8b,
0x001455ac,
0x00102bbc,
0xe000ed00,
0x00102bcc,
0x00102c18,
0x00102c4c,
0x00102dec,
0x00102e0c,
0x00102e30,
0x00102e3c,
0x00102e48,
0x00102e20,
0x00102dfc,
0x00102d88,
0x00102d00,
0x00102d78,
0x00102c8c,
0x00102cf0,
0x00102e9c,
0x00102e88,
0x00102e94,
0x00102e7c,
0x4802b508,
0xfa5af7ff,
0xbf00e7fe,
0x00102ea8,
0x4a15b508,
0x68134604,
0xd0fc2b00,
0xf7ff4813,
0x2c30fa4d,
0x2c40d013,
0x2c20d019,
0x4810d013,
0xfa44f7ff,
0xf7ff480f,
0xf7fffa41,
0x480efecd,
0xfa3cf7ff,
0x22014b08,
0xf7ff601a,
0x480bffd9,
0xfa34f7ff,
0x480ae7ee,
0xfa30f7ff,
0x4809e7ea,
0xfa2cf7ff,
0xbf00e7e6,
0x40044040,
0x00102eb4,
0x00102f04,
0x00102f10,
0x00102f1c,
0x00102eec,
0x00102edc,
0x00102ef8,
0x0310f04f,
0xb80cf000,
0x0320f04f,
0xb808f000,
0x0330f04f,
0xb804f000,
0x0340f04f,
0xb800f000,
0x8008f3ef,
0x0104f04f,
0x420a4672,
0xf3efd001,
0x469c8009,
0x68024924,
0x3104600a,
0x600a6842,
0x68823104,
0x3104600a,
0x600a68c2,
0xc1f03104,
0x600f4647,
0x464f3104,
0x3104600f,
0x600f4657,
0x465f3104,
0x3104600f,
0x600a6902,
0x69423108,
0x3104600a,
0x600a6982,
0x69c23104,
0x3104600a,
0x33204603,
0x7600f44f,
0xd0004232,
0x46753304,
0x0610f04f,
0xd1004235,
0x460c3348,
0x60233c10,
0x8209f3ef,
0x3104600a,
0x8208f3ef,
0x3104600a,
0x600a4672,
0xf3ef3104,
0x600a8214,
0x46604b03,
0x47984901,
0x0000e7fe,
0x001455ac,
0x00101691,
0x8305f3ef,
0x4a06b923,
0xb1136813,
0x60133301,
0xf3ef4770,
0x4b038110,
0xb6726019,
0xe7f56813,
0x00145420,
0x0014541c,
0x8305f3ef,
0x4a05b943,
0x3b016813,
0xb91b6013,
0x681b4b03,
0x8810f383,
0xbf004770,
0x00145420,
0x0014541c,
0xf000b510,
0xf000fcc7,
0xf7fff871,
0x4812f9e3,
0xf982f7ff,
0x46082100,
0xfc74f000,
0xf7ffb662,
0xf7fffb45,
0xf3effbd5,
0xf0138310,
0xd10b0401,
0xf7ffb672,
0xb158fd7b,
0xf7ffb662,
0xf3effbc9,
0xf0138310,
0xd0f30401,
0xfd70f7ff,
0xd1e82800,
0x2c00bf30,
0xe7e4d0f0,
0x00102f38,
0x4a074b06,
0x70c0f503,
0x1f04f853,
0x1f04f842,
0xd1f94283,
0x4a044b03,
0x4770609a,
0x000ffffc,
0x0013fffc,
0xe000ed00,
0x00140000,
0x4c13b570,
0x46034d13,
0x60232003,
0xfd48f000,
0x68234a11,
0xfbb06811,
0x00c3f0f3,
0x0470f003,
0x0342f3c0,
0xf0414323,
0xf0000180,
0x60110401,
0x490a4423,
0xf3c04c0a,
0xf3c01607,
0x602e3007,
0x600b6020,
0xf0236813,
0x60130380,
0xbf00bd70,
0x00145424,
0x40041000,
0x4004100c,
0x40041028,
0x40041004,
0x4b1eb538,
0x07db681b,
0x4a1dd42e,
0x2b006813,
0x4c1cd0fc,
0x4d1d491c,
0x481e4a1d,
0x60232300,
0x602b2401,
0x6813600c,
0xf443491b,
0x24037380,
0x60046013,
0xf5b3680b,
0xd1192f61,
0x48134b11,
0x4c0f4916,
0x25074a0d,
0x6803601d,
0x0301f043,
0x25016003,
0x3380f44f,
0x602520fc,
0x0310f881,
0x6813600b,
0x6013432b,
0x22014b0d,
0xbd38601a,
0x2061f44f,
0xff92f7ff,
0xbf00e7e0,
0x40044080,
0x40044040,
0x40041008,
0x40041024,
0x40041004,
0x40041010,
0x4004100c,
0x00145424,
0xe000e100,
0x00145428,
0x68134a03,
0xd4fc031b,
0x60184b02,
0xbf004770,
0x40041020,
0x40041000,
0x681b4b0e,
0x030ff003,
0xd80a2b0c,
0xf003e8df,
0x09090907,
0x090d0910,
0x09090909,
0x4b08000a,
0x4770681b,
0x681b4b07,
0x4b074770,
0x4770681b,
0x681b4b06,
0xd0f52b00,
0xbf004718,
0x40041008,
0x40041018,
0x40041000,
0x40041014,
0x0014542c,
0x681b4b0e,
0x030ff003,
0xd80a2b0c,
0xf003e8df,
0x09090907,
0x090d0910,
0x09090909,
0x4b08000a,
0x4770681b,
0x681b4b07,
0x4b074770,
0x4770681b,
0x681b4b06,
0xd0f52b00,
0xbf004718,
0x40042008,
0x40042018,
0x40042000,
0x40042014,
0x00145430,
0x681b4b0e,
0x030ff003,
0xd80a2b0c,
0xf003e8df,
0x09090907,
0x090d0910,
0x09090909,
0x4b08000a,
0x4770681b,
0x681b4b07,
0x4b074770,
0x4770681b,
0x681b4b06,
0xd0f52b00,
0xbf004718,
0x40043008,
0x40043018,
0x40043000,
0x40043014,
0x00145434,
0x4ff8e92d,
0xf894680c,
0x2b00303a,
0x460dd14e,
0x47986843,
0x6a1b682b,
0xd0474298,
0x5202e9d4,
0x4b386a26,
0x1b866220,
0x429d4016,
0xf04f4630,
0xd0340100,
0xc03bf894,
0x0f00f1bc,
0xfba6d038,
0xf1cc6703,
0xfa260220,
0xfa07f00c,
0xf1acf202,
0x43100320,
0xf303fa27,
0xf1ac4318,
0xe9d40a20,
0xfa27320a,
0xfa00f10c,
0xfa01fa0a,
0xea4efe0c,
0xf1cc0e0a,
0x18f30a20,
0xfa0afa20,
0xfc0cfa00,
0x0202eb47,
0x0e0aea4e,
0x080cebb3,
0x090eeb62,
0x45b12600,
0x45a8bf08,
0xe9c4d22a,
0xe9d4890a,
0x1818320c,
0x0101eb42,
0x010ce9c4,
0x8ff8e8bd,
0x0900f04f,
0x0103fba6,
0x464b462a,
0xfc72f000,
0xe9d446a8,
0xeb12560a,
0xeb430a05,
0x45cb0b06,
0x45c2bf08,
0xe9c4d202,
0xe7e0ab0a,
0xf1413001,
0xebba0100,
0xeb6b0308,
0xe9c40209,
0xe7d6320a,
0xf1413001,
0xebb80100,
0xeb690205,
0xe9c40306,
0xe7cc230a,
0x000f4240,
0x4ff0e92d,
0xf8956845,
0xb081303a,
0xf895b913,
0xb1133039,
0xe8bdb001,
0x46018ff0,
0xf8514604,
0xf7ff0b04,
0x6866ff69,
0x29006871,
0xe9d6d04c,
0xe9d1230c,
0x428b0100,
0x4282bf08,
0xe9d6d23e,
0xebb0ab06,
0xeb610802,
0x45cb0903,
0x45c2bf08,
0xd3236937,
0x4b2e68b2,
0xd048429a,
0x303bf896,
0xd0482b00,
0x0020f1a3,
0xf000fa08,
0xf203fa09,
0xf1c34302,
0x48270120,
0xf101fa28,
0xf803fa08,
0xeb18430a,
0xf04f0000,
0xeb420100,
0x4a200101,
0xf0002300,
0x4287fc03,
0x4607bf28,
0x68f26a31,
0x187e6823,
0x691b4016,
0x47984630,
0x685b6823,
0x6a2b4798,
0xd21242b3,
0xd31542b0,
0x695b6823,
0xe8bdb001,
0x47184ff0,
0x69296a2b,
0x68e86822,
0x440b6912,
0xb0014018,
0x4ff0e8bd,
0x42834710,
0x42b0d998,
0xe7e9d396,
0xd8e74283,
0x4547e792,
0x4647bf28,
0x4807e7d2,
0xab08fba2,
0xbb09fb02,
0x0000eb1a,
0x0100f04f,
0x0101eb4b,
0xbf00e7bf,
0x000f4240,
0x000f423f,
0x4ff0e92d,
0x46806803,
0xb083681b,
0xf8d84798,
0x69db3000,
0x68064798,
0xd0552e00,
0x3cfff116,
0x0300f04f,
0xf1434632,
0x241f31ff,
0x0e01f04f,
0x3c01e001,
0xfa0ed056,
0x42b5f504,
0xd1f8b2e7,
0x1f056840,
0xd8462d1c,
0xf04f4c27,
0xf04f0a07,
0xfa0a0901,
0xfa09fa05,
0xfb8af900,
0xf1094504,
0xeb1c39ff,
0xeb450004,
0xf0000101,
0xe9d8fb8b,
0x25003200,
0x5500e9c2,
0x9201685c,
0x9000468b,
0xf8d847a0,
0x9a014004,
0x62109b00,
0xf8844641,
0xf851703b,
0x61a30b04,
0x23002200,
0xe9c42701,
0xe9c46902,
0xe9c4230a,
0xf8c4230c,
0xf8c4b01c,
0xf884a010,
0x8727503a,
0xfe92f7ff,
0xb0034640,
0x4ff0e8bd,
0xbf10f7ff,
0xf8df4a07,
0x2300c024,
0x46194616,
0x4d05e7a9,
0x39fff04f,
0xf04f2400,
0xe7be4ae0,
0xe7ab4627,
0x000f4240,
0x0006acfc,
0x000f423f,
0x43f8e92d,
0xf7ff4681,
0xf8d9fcff,
0x68db3000,
0xf8d94798,
0xf8933004,
0xbb12203a,
0xf8832201,
0xf1092039,
0x685a0804,
0xf8d9e012,
0xf7ff0000,
0xf8d9fe5d,
0x68593004,
0x670ce9d3,
0x4500e9d1,
0xbf0842af,
0xd30642a6,
0x68ca681c,
0xb964605a,
0x2a004641,
0x2200d1e9,
0xf8834648,
0xf7ff2039,
0xe8bdfec9,
0xf7ff43f8,
0x6888bce3,
0xf8d947a0,
0xe7d83004,
0x6843b538,
0x2038f893,
0xb9224604,
0x303af893,
0xf7ffb90b,
0xf7ffff41,
0x4621fcbd,
0x0b04f851,
0xfe2af7ff,
0xe9d36863,
0xf7ff450c,
0x4620fcc7,
0xbd384629,
0x47704800,
0x00102f48,
0x6bd34a07,
0xbf440759,
0x3100f44f,
0x07db6391,
0x4770d400,
0xf44f4b02,
0x639a3280,
0xb88ef000,
0x40106000,
0x4b20b538,
0xb122781a,
0xf44f4b1f,
0x639a7280,
0x2401bd38,
0x701c2002,
0xfa46f000,
0xfba24a1b,
0x0c923200,
0x21044623,
0x0f01f012,
0x0252ea4f,
0x3901d103,
0x0343ea4f,
0xfbb0d1f6,
0x4d13f0f3,
0x4a114913,
0xfba54c13,
0x25105000,
0x5108f8c1,
0xf8c12540,
0x6a115110,
0x0c803b01,
0x0310f043,
0xf0213801,
0x62110101,
0x62906353,
0x20fc6a13,
0x0301f043,
0xf04f6213,
0xf8845180,
0x6061033c,
0xbf00bd38,
0x00145438,
0x40106000,
0x431bde83,
0x40100000,
0xe000e100,
0x6a584b01,
0xbf004770,
0x40106000,
0x22014b02,
0x639a6318,
0xbf004770,
0x40106000,
0xf04f4b02,
0xf8c35280,
0x47702104,
0xe000e100,
0xf44f4b02,
0x639a7280,
0xbf004770,
0x40106000,
0xf44f4b02,
0x639a3280,
0xbf004770,
0x40106000,
0x490b4b0a,
0xb4106a1a,
0x0201f022,
0x7480f44f,
0x5080f04f,
0x639c621a,
0x0084f8c1,
0x8f4ff3bf,
0x8f6ff3bf,
0x4b04f85d,
0xbf004770,
0x40106000,
0xe000e100,
0x681b4b02,
0x4802b10b,
0x47704718,
0x00140184,
0x00102f50,
0x47704800,
0x00102f7c,
0x68d34a07,
0xbf440419,
0x0100f44f,
0x059b6091,
0x4770d400,
0xf44f4b02,
0x609a3200,
0xb88ef000,
0x40501000,
0x781a4b15,
0x4a15bb1a,
0x70192101,
0x07986dd3,
0xf5a2d115,
0x681342a0,
0xd10a4019,
0x7340f423,
0x7390f443,
0x0301f043,
0x61112011,
0x60506151,
0x049a6013,
0x4a0ad403,
0x5300f443,
0x4b096013,
0xf04f21fc,
0xf8835280,
0x601a131c,
0x4b044770,
0x7200f44f,
0x4770609a,
0x00145480,
0x40506000,
0x40501000,
0xe000e100,
0x490b4b0a,
0xb410681a,
0x5200f422,
0x7400f44f,
0x5080f04f,
0x609c601a,
0x0080f8c1,
0x8f4ff3bf,
0x8f6ff3bf,
0x4b04f85d,
0xbf004770,
0x40501000,
0xe000e100,
0x22024b02,
0x609a6298,
0xbf004770,
0x40501000,
0xf04f4b02,
0xf8c35280,
0x47702100,
0xe000e100,
0xf44f4b02,
0x609a7200,
0xbf004770,
0x40501000,
0xf44f4b02,
0x609a3200,
0xbf004770,
0x40501000,
0x490bb430,
0x690ab084,
0xe9cd2300,
0x690a2300,
0xe9cd2300,
0xe9dd2302,
0xe9dd4500,
0x429d2302,
0x4294bf08,
0xe9ddd1ef,
0xb0040102,
0x4770bc30,
0x40501000,
0x47704800,
0x00102f84,
0x681b4b02,
0x4802b10b,
0x47704718,
0x00140188,
0x00102f84,
0x4c07b538,
0x4a084d07,
0x60286823,
0xb1036011,
0xf7ffbd38,
0x6020ffe7,
0x4038e8bd,
0xbe7ef7ff,
0x001454d0,
0x001454c8,
0x001454cc,
0x20014b03,
0x22002102,
0x609960d8,
0x4770601a,
0x40104000,
0x4c11b570,
0xb1f06a20,
0x25014e10,
0x6963e008,
0xf000fa23,
0xf00043c0,
0x47900001,
0xb1906a20,
0xf080fab0,
0x001ff1c0,
0xf300fa05,
0xf3bf6263,
0xf8568f6f,
0x2a002020,
0x6923d0f0,
0x07db40c3,
0x2002d5e5,
0xbd70e7e9,
0x40504000,
0x001454d4,
0x2000b508,
0xf8c6f000,
0x46024b0a,
0x601a2001,
0xf8c0f000,
0x46024b08,
0x601a2002,
0xf8baf000,
0x46024b06,
0x601a2006,
0xf8b4f000,
0x60184b04,
0xbf00bd08,
0x0014018c,
0x00140198,
0x00140190,
0x00140194,
0xf8d24a0a,
0xf4433088,
0xf8c20370,
0x69133088,
0x0310f043,
0x68d36113,
0x01fff64f,
0xf043400b,
0xf44363bf,
0x60d33300,
0x4770b662,
0xe000ed00,
0xf1030183,
0xf5034380,
0xf24123e0,
0x585a010c,
0x127cf412,
0x4770d100,
0x4d07b430,
0xf855585c,
0xea445020,
0x505c2402,
0x4601b125,
0x2000462b,
0x4718bc30,
0x4770bc30,
0x00145554,
0xf7ff2004,
0xbf00bfdf,
0xf7ff2001,
0xbf00bfdb,
0xf7ff2002,
0xbf00bfd7,
0xf7ff2003,
0xbf00bfd3,
0xf2414a2c,
0x58d1334c,
0xd50d0349,
0x492ab410,
0xbb517809,
0x482958d1,
0x6180f041,
0x50d12402,
0xf85d6004,
0x47704b04,
0x034858d1,
0x58d0d503,
0x6080f040,
0x050b50d0,
0xf3efd516,
0x491d8005,
0x324cf241,
0xf043588b,
0x508b6300,
0xf3efb948,
0xf0138310,
0xd1040301,
0x4a19b672,
0xb6626353,
0x4b174770,
0x635a2200,
0x29014770,
0xd0d258d1,
0xd5030348,
0xf04058d0,
0x50d06080,
0xd5d0050c,
0x8005f3ef,
0xf241490b,
0x588b324c,
0x6300f043,
0xb948508b,
0x8310f3ef,
0x0301f013,
0xb672d104,
0x63534a07,
0xe7bcb662,
0xf85d4b05,
0x22004b04,
0x4770635a,
0x40070000,
0x0014558c,
0x001455a0,
0x00145600,
0x4b3bb510,
0xcb0f4604,
0xf10db084,
0xe90c0c10,
0x2c07000f,
0xe8dfd865,
0x3408f004,
0x3e5d2529,
0x4b340444,
0x07db685b,
0x4b33d539,
0x06d0685a,
0x6859d535,
0xa804699a,
0xf282fa50,
0xf81204c9,
0xd44c2c10,
0x4b2d6859,
0xf411482d,
0xbf087f80,
0x06144618,
0x0040bf44,
0x027ff002,
0xf0f2fbb0,
0xbd10b004,
0x685b4b23,
0xd5180798,
0x20014b21,
0x4084f8d3,
0xffc4f7ff,
0xfbb0b2e4,
0xb004f0f4,
0x4b1dbd10,
0x695c2000,
0xffbaf7ff,
0xfbb0b2e4,
0xb004f0f4,
0x4b17bd10,
0x071a685b,
0x4819d4e6,
0x4b15e7de,
0x6b1a4918,
0x48166adb,
0xfa54ac04,
0xf012f383,
0xf9130f01,
0xf8132c10,
0xbf183c10,
0x2a004608,
0xf003bfbc,
0x0040037f,
0xf0f3fbb0,
0xbd10b004,
0x685b4b07,
0xd4c70759,
0x480ae7df,
0x480ae7b7,
0x2287490a,
0xfbc4f7fe,
0xe7b72000,
0x00102fe0,
0x40100000,
0x40500000,
0x1c9c3800,
0x1312d000,
0x03197500,
0x39387000,
0x0010294c,
0x00102fb0,
0xb94ab953,
0xbf082900,
0xbf1c2800,
0x31fff04f,
0x30fff04f,
0xb96ef000,
0x0c08f1ad,
0xce04e96d,
0xf806f000,
0xe004f8dd,
0x2302e9dd,
0x4770b004,
0x47f0e92d,
0x46049d08,
0x2b00468c,
0x8083f040,
0x4617428a,
0xfab2d947,
0xb142f282,
0x0020f1c2,
0xf000fa24,
0x40974091,
0x0c01ea40,
0xea4f4094,
0x0c234817,
0xf6f8fbbc,
0xfe87fa1f,
0xc116fb08,
0x4301ea43,
0xf10efb06,
0xd9094299,
0xf10618fb,
0xf08030ff,
0x42998119,
0x8116f240,
0x443b3e02,
0xb2a41a5b,
0xf0f8fbb3,
0x3310fb08,
0x4403ea44,
0xfe0efb00,
0xd90945a6,
0xf100193c,
0xf08033ff,
0x45a68105,
0x8102f240,
0x443c3802,
0x4006ea40,
0x040eeba4,
0xb11d2600,
0x230040d4,
0x4300e9c5,
0xe8bd4631,
0xb90287f0,
0xfab2deff,
0x2a00f282,
0x1bcbd150,
0x4e17ea4f,
0xf887fa1f,
0xfbb32601,
0x0c21fcfe,
0x331cfb0e,
0x4103ea41,
0xf30cfb08,
0xd907428b,
0xf10c1879,
0xd20230ff,
0xf200428b,
0x468480e9,
0xb2a31ac9,
0xf0fefbb1,
0x1110fb0e,
0x4401ea43,
0xf800fb08,
0xd90745a0,
0xf100193c,
0xd20233ff,
0xf20045a0,
0x461880d9,
0x0408eba4,
0x400cea40,
0x428be7bf,
0x2d00d909,
0x80b1f000,
0xe9c52600,
0x46300100,
0xe8bd4631,
0xfab387f0,
0x2e00f683,
0x428bd14a,
0x4282d302,
0x80b8f200,
0xeb611a84,
0x20010103,
0x2d00468c,
0xe9c5d0a8,
0xe7a54c00,
0x0320f1c2,
0xf603fa20,
0xfa014097,
0xea4ff002,
0x40d94e17,
0x0c034330,
0xf6fefbb1,
0xf887fa1f,
0x1116fb0e,
0x4301ea43,
0xf108fb06,
0xfa044299,
0xd909f402,
0xf10618fb,
0xf0803cff,
0x4299808d,
0x808af240,
0x443b3e02,
0xb2811a5b,
0xf0fefbb3,
0x3310fb0e,
0x4103ea41,
0xf308fb00,
0xd907428b,
0xf1001879,
0xd2733cff,
0xd971428b,
0x44393802,
0xea401acb,
0xe7784606,
0x0c20f1c6,
0xf406fa03,
0xf30cfa22,
0xfa20431c,
0xfa01f70c,
0xea4ff306,
0xfa214e14,
0x431ff10c,
0xfbb10c3b,
0xfa1ff9fe,
0xfb0ef884,
0xea431119,
0xfb094101,
0x458afa08,
0xf206fa02,
0xf306fa00,
0x1861d908,
0x30fff109,
0x458ad248,
0xf1a9d946,
0x44210902,
0x010aeba1,
0xfbb1b2bf,
0xfb0ef0fe,
0xea471110,
0xfb004701,
0x45b8f808,
0x19e7d907,
0x31fff100,
0x45b8d22e,
0x3802d92c,
0xea404427,
0xeba74009,
0xfba00708,
0x454f8902,
0x464946c6,
0xd017d31a,
0xebb3b15d,
0xeb67020e,
0xfa070701,
0x40f2fc0c,
0x0202ea4c,
0xe9c540f7,
0x26002700,
0xe8bd4631,
0x462e87f0,
0xe70b4628,
0xe6e94606,
0xe6fd4618,
0xd2e54543,
0x0e02ebb8,
0x0104eb69,
0xe7df3801,
0xe7d24608,
0xe78d4660,
0xe7b94681,
0xe7754666,
0xe74a4630,
0x0c02f1ac,
0xe7134439,
0x443c3802,
0xbf00e724,
0xbf004770,
0xea414684,
0xf0130300,
0xd16d0303,
0xd3413a40,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0xd2bd3a40,
0xd3113230,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0x3b04f851,
0x3b04f840,
0xd2ed3a10,
0xd305320c,
0x3b04f851,
0x3b04f840,
0xd2f93a04,
0xd0083204,
0xbf1c07d2,
0x3b01f811,
0x3b01f800,
0x880bd301,
0x46608003,
0xbf004770,
0xd3132a08,
0xd08d078b,
0x0303f010,
0xf1c3d08a,
0x1ad20304,
0xbf1c07db,
0x3b01f811,
0x3b01f800,
0xf831d380,
0xf8203b02,
0xe77b3b02,
0xd3d93a04,
0xf8113a01,
0xf8003b01,
0xd2f93b01,
0x7003780b,
0x7043784b,
0x7083788b,
0x47704660,
0x0786b4f0,
0x1e54d046,
0xd03c2a00,
0x4603b2ca,
0x3c01e001,
0xf803d337,
0x079d2b01,
0x2c03d1f9,
0xb2cdd92a,
0x2505ea45,
0xea452c0f,
0xd9344505,
0x0210f1a4,
0x0c0ff022,
0x0720f103,
0x44670916,
0x0210f103,
0x5504e942,
0x5502e942,
0x42ba3210,
0x1c72d1f8,
0x0f0cf014,
0x1202eb03,
0x060ff004,
0x1f33d013,
0x0303f023,
0x44133304,
0x5b04f842,
0xd1fb4293,
0x0403f006,
0xb2cab12c,
0xf803441c,
0x429c2b01,
0xbcf0d1fb,
0x46344770,
0x2c004613,
0xe7f8d1f3,
0x46034614,
0x461ae7c1,
0xe7e04626,
0x6d5c2e2e,
0x6c75646f,
0x645c7365,
0x735c6762,
0x645c6372,
0x705f6762,
0x746e6972,
0x0000632e,
0x00000030,
0x5f474244,
0x5f564553,
0x204e494d,
0x70203d3c,
0x69666572,
0x26262078,
0x65727020,
0x20786966,
0x4244203c,
0x45535f47,
0x414d5f56,
0x00000058,
0x33323130,
0x37363534,
0x62613938,
0x66656463,
0x00000000,
0x33323130,
0x37363534,
0x42413938,
0x46454443,
0x00000000,
0x00000100,
0x00000000,
0x02040000,
0x07060203,
0x02040000,
0x07060203,
0x03040000,
0x07060003,
0x05000000,
0x07060005,
0x05000000,
0x07060005,
0x00000000,
0x07000000,
0x00000100,
0x00000000,
0x45535341,
0x65205452,
0x726f7272,
0x4625203a,
0x0064253a,
0x5353419b,
0x20545245,
0x29732528,
0x20746120,
0x253a7325,
0x00000a64,
0x5f707364,
0x5f67736d,
0x646e6168,
0x0a72656c,
0x00000000,
0x5f653261,
0x3a67736d,
0x25206425,
0x64252064,
0x0000000a,
0x5f653261,
0x61746164,
0x7274705f,
0x0a58253a,
0x00000000,
0x6d5c2e2e,
0x6c75646f,
0x645c7365,
0x735c7073,
0x645c6372,
0x615f7073,
0x632e6970,
0x00000000,
0x5f653261,
0x61746164,
0x6f6f705f,
0x5d695b6c,
0x7461642e,
0x74705f61,
0x3d212072,
0x4c554e20,
0x0000004c,
0x5f613265,
0x61746164,
0x7274705f,
0x0a58253a,
0x00000000,
0x5f613265,
0x61746164,
0x6f6f705f,
0x5d695b6c,
0x7461642e,
0x74705f61,
0x3d212072,
0x4c554e20,
0x0000004c,
0x20707364,
0x74696e69,
0x61747320,
0x000a7472,
0x20707364,
0x74696e69,
0x6e6f6420,
0x00000a65,
0x5f707364,
0x61746164,
0x6e61685f,
0x72656c64,
0x0000000a,
0x5f653261,
0x61746164,
0x2064253a,
0x25206425,
0x00000a64,
0x61746164,
0x6e65735f,
0x643e2d64,
0x5f617461,
0x3a727470,
0x000a5825,
0x36315f78,
0x3a746962,
0x79205825,
0x6236315f,
0x253a7469,
0x65722058,
0x746c7573,
0x3130253a,
0x000a5836,
0x6d5c2e2e,
0x6c75646f,
0x645c7365,
0x735c7073,
0x645c6372,
0x655f7073,
0x746e6576,
0x0000632e,
0x656e696c,
0x20736920,
0x66206425,
0x20656c69,
0x25207369,
0x00000073,
0x6d5c2e2e,
0x6c75646f,
0x635c7365,
0x6f6d6d6f,
0x72735c6e,
0x6f635c63,
0x73696c5f,
0x00632e74,
0x7473696c,
0x7264685f,
0x203d2120,
0x4c4c554e,
0x00000000,
0x2d25520a,
0x203a6434,
0x58383025,
0x00000000,
0x2050530a,
0x203a2020,
0x58383025,
0x20524c0a,
0x203a2020,
0x58383025,
0x2043500a,
0x203a2020,
0x58383025,
0x5350780a,
0x203a2052,
0x58383025,
0x5053500a,
0x203a2020,
0x58383025,
0x50534d0a,
0x203a2020,
0x58383025,
0x00000000,
0x5550430a,
0x203a4449,
0x58383025,
0x5343490a,
0x203a2052,
0x58383025,
0x4f54560a,
0x203a2052,
0x58383025,
0x5249410a,
0x203a5243,
0x58383025,
0x00000000,
0x4348530a,
0x203a5253,
0x58383025,
0x5346430a,
0x203a2052,
0x58383025,
0x5346480a,
0x203a2052,
0x58383025,
0x5346440a,
0x203a2052,
0x58383025,
0x5346410a,
0x203a2052,
0x58383025,
0x00000000,
0x464d4d0a,
0x203a5253,
0x58323025,
0x4920200a,
0x56434341,
0x204c4f49,
0x0964253a,
0x43434144,
0x4c4f4956,
0x64253a20,
0x4d20200a,
0x54534e55,
0x5252454b,
0x0964253a,
0x4b54534d,
0x20525245,
0x64253a20,
0x4d20200a,
0x4550534c,
0x20205252,
0x0964253a,
0x52414d4d,
0x494c4156,
0x64253a44,
0x00000000,
0x464d4d0a,
0x203a5241,
0x58383025,
0x00000000,
0x5346420a,
0x203a2052,
0x58323025,
0x4920200a,
0x45535542,
0x20205252,
0x253a2020,
0x52500964,
0x53494345,
0x3a525245,
0x200a6425,
0x504d4920,
0x49434552,
0x52524553,
0x0964253a,
0x54534e55,
0x5252454b,
0x64253a20,
0x5320200a,
0x52454b54,
0x20202052,
0x253a2020,
0x534c0964,
0x52524550,
0x3a202020,
0x200a6425,
0x41464220,
0x4c415652,
0x20204449,
0x0064253a,
0x4146420a,
0x203a2052,
0x58383025,
0x00000000,
0x5346550a,
0x203a2052,
0x58343025,
0x5520200a,
0x4645444e,
0x54534e49,
0x64253a52,
0x564e4909,
0x54415453,
0x253a2045,
0x20200a64,
0x50564e49,
0x20202043,
0x253a2020,
0x4f4e0964,
0x20205043,
0x3a202020,
0x200a6425,
0x414e5520,
0x4e47494c,
0x3a204445,
0x44096425,
0x59425649,
0x4f52455a,
0x0064253a,
0x646f4d0a,
0x203a2065,
0x65726854,
0x00006461,
0x6972500a,
0x203a2076,
0x72657355,
0x00000000,
0x6972500a,
0x203a2076,
0x76697250,
0x67656c69,
0x00006465,
0x646f4d0a,
0x203a2065,
0x646e6148,
0x0072656c,
0x6174530a,
0x203a6b63,
0x00505350,
0x6174530a,
0x203a6b63,
0x0050534d,
0x544e430a,
0x203a4c52,
0x58383025,
0x414d500a,
0x203a4b53,
0x58383025,
0x414d460a,
0x203a4b53,
0x58383025,
0x5341420a,
0x203a5045,
0x58383025,
0x00000000,
0x6d75440a,
0x50534d70,
0x0000003a,
0x30255b0a,
0x3a5d7838,
0x00000000,
0x38302520,
0x00000058,
0x6d75440a,
0x50535070,
0x0000003a,
0x696e6150,
0x2e2e2e63,
0x0000000a,
0x202b2b0a,
0x20344d43,
0x6c756146,
0x61482074,
0x656c646e,
0x2b2b2072,
0x61460a0a,
0x54746c75,
0x3a657079,
0x00000020,
0x4d6d654d,
0x67616e61,
0x75614665,
0x0000746c,
0x46737542,
0x746c7561,
0x00000000,
0x67617355,
0x75614665,
0x0000746c,
0x64726148,
0x6c756146,
0x00000074,
0x6f430a0a,
0x7865746e,
0x00003a74,
0x2d2d0a0a,
0x344d4320,
0x75614620,
0x4820746c,
0x6c646e61,
0x2d207265,
0x000a0a2d,
0x73640a0d,
0x74732070,
0x0d747261,
0x0000000a,
0x000f4240,
0x00000020,
0x00102f58,
0x00145440,
0x00101ea5,
0x00101f3d,
0x00101f69,
0x00101f79,
0x00101f49,
0x00101f59,
0x00101f89,
0x00101e79,
0x00000000,
0x000f4240,
0x00000020,
0x00102f8c,
0x00145488,
0x00101ffd,
0x001020d9,
0x001020b9,
0x001020c9,
0x00102099,
0x001020a9,
0x00102065,
0x00101fd1,
0x00000001,
0x705c2e2e,
0x615c666c,
0x38386369,
0x735c3030,
0x645c6372,
0x65766972,
0x79735c72,
0x72746373,
0x79735c6c,
0x72746373,
0x70615f6c,
0x00632e69,
0x080c1018,
0x058b0607,
0x03870489,
0x01180285,
0x00000000,
0xbf00b5f8,
0xbf00b5f8,
0x7fffe70c,
0x00000001,
0x00000001,
0x00101dd1,
0x00101dd1,
0x02625a00,
0x03197500,
0x03197500,
0x02625a00,

};

void dsp_image_load(uint32_t addr, bool use_dma, uint8_t dma_ch, bool image_check)
{
    uint8_t *image = (uint8_t *)dsp_image_table;
    uint32_t len = sizeof(dsp_image_table);

    if (0 == len) {
        return;
    }

    if (use_dma) {
        cpusysctrl_hclkme_set(CSC_HCLKME_DMA_EN_BIT);
        dma_desc_t dma_desc0;
        dma_desc0.SAR = (uint32_t)image;
        dma_desc0.DAR = (uint32_t)addr;
        dma_desc_length_set(&dma_desc0, len);
        dma_desc0.LNAR = (uint32_t)0;
        dma_push(&dma_desc0, &dma_desc0, dma_ch);
        dma_lli_poll(dma_ch);
        dma_ch_int_clear(dma_ch);
    } else {
        memcpy((void *)addr, (void *)image, len);
    }

    if (image_check) {
        uint32_t *dst = (uint32_t *)addr;
        uint32_t *src = (uint32_t *)dsp_image_table;
        uint32_t len_in_word = len / 4;
        uint32_t idx = 0;
        bool check_pass = true;

        for (idx = 0; idx < len_in_word; idx++) {
            if (src[idx] != dst[idx]) {
                check_pass = false;
                break;
            }
        }

        TRACE("image_check:%d idx:0x%X\n", check_pass, idx);
    }
}

