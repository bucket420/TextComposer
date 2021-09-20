const unsigned char resources[] = {
	0x53,0x41,0x72,0x00,0x09,0x00,0x00,0x00,0x6d,0x00,0xff,0xff,0x01,0x00,0xff,0xff,0x61,0x00,0xff,0xff,0x02,0x00,0xff,0xff,0x69,0x00,0xff,0xff,0x03,0x00,0xff,0xff,0x6e,0x00,0xff,0xff,0x04,0x00,0xff,0xff,0x2e,
	0x00,0xff,0xff,0x05,0x00,0xff,0xff,0x68,0x00,0xff,0xff,0x06,0x00,0xff,0xff,0x74,0x00,0xff,0xff,0x07,0x00,0xff,0xff,0x6d,0x00,0xff,0xff,0x08,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x01,0x00,0xff,0xff,0x01,0x00,
	0x00,0x00,0x60,0x00,0x00,0x00,0x22,0x05,0x00,0x00,0xb8,0x0c,0x00,0x00,0x0c,0x3c,0x68,0x74,0x6d,0x6c,0x3e,0x0d,0x0a,0x3c,0x68,0x65,0x61,0x64,0x20,0x07,0x00,0x20,0x20,0x00,0x14,0x3c,0x74,0x69,0x74,0x6c,0x65,
	0x3e,0x54,0x65,0x78,0x74,0x43,0x6f,0x6d,0x70,0x6f,0x73,0x65,0x72,0x3c,0x2f,0x80,0x13,0xa0,0x20,0x02,0x73,0x74,0x79,0xe0,0x00,0x0c,0x40,0x00,0x40,0x44,0x01,0x20,0x7b,0xe0,0x01,0x0f,0x40,0x00,0x1f,0x62,0x61,
	0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x3a,0x20,0x6c,0x69,0x6e,0x65,0x61,0x72,0x2d,0x67,0x72,0x61,0x64,0x69,0x65,0x6e,0x74,0x28,0x30,0x64,0x65,0x67,0x12,0x2c,0x20,0x23,0x46,0x46,0x35,0x45,0x35,0x45,0x2c,
	0x20,0x79,0x65,0x6c,0x6c,0x6f,0x77,0x29,0x3b,0xe0,0x01,0x40,0x00,0x7d,0xe0,0x01,0x0a,0x03,0x62,0x6f,0x64,0x79,0xe0,0x07,0x5b,0x15,0x76,0x65,0x72,0x74,0x69,0x63,0x61,0x6c,0x2d,0x61,0x6c,0x69,0x67,0x6e,0x3a,
	0x20,0x6d,0x69,0x64,0x64,0x6c,0x65,0xe0,0x02,0x3f,0x40,0x00,0x00,0x6f,0x20,0x25,0x00,0x66,0x20,0x57,0x01,0x3a,0x68,0x20,0x1d,0x01,0x65,0x6e,0xe0,0x02,0x1d,0xe0,0x02,0x5d,0x05,0x2e,0x69,0x6e,0x70,0x75,0x74,
	0xe0,0x07,0x5f,0x12,0x6d,0x61,0x72,0x67,0x69,0x6e,0x2d,0x62,0x6f,0x74,0x74,0x6f,0x6d,0x3a,0x20,0x32,0x30,0x70,0x78,0xe0,0x02,0x3e,0x40,0x00,0x21,0x15,0x03,0x69,0x74,0x69,0x6f,0x20,0x7b,0x06,0x72,0x65,0x6c,
	0x61,0x74,0x69,0x76,0xe0,0x03,0x7d,0xe0,0x03,0x5f,0xe0,0x0b,0xbe,0x80,0x5e,0x04,0x3a,0x20,0x31,0x30,0x25,0x40,0x03,0xe0,0x02,0x39,0x40,0x00,0x09,0x70,0x61,0x64,0x64,0x69,0x6e,0x67,0x3a,0x20,0x35,0x20,0x76,
	0x20,0x1f,0xe0,0x08,0x7b,0xe1,0x13,0x59,0x01,0x34,0x35,0x61,0x5a,0x16,0x64,0x65,0x65,0x70,0x73,0x6b,0x79,0x62,0x6c,0x75,0x65,0x2c,0x20,0x63,0x68,0x61,0x72,0x74,0x72,0x65,0x75,0x73,0x65,0xe1,0x03,0x62,0x40,
	0x00,0x05,0x62,0x6f,0x72,0x64,0x65,0x72,0x20,0x69,0x20,0x68,0x04,0x73,0x6f,0x6c,0x69,0x64,0xe0,0x0c,0x1f,0x00,0x2d,0x40,0x5c,0x01,0x75,0x73,0xe1,0x35,0x07,0x61,0x67,0x07,0x2d,0x77,0x72,0x61,0x70,0x70,0x65,
	0x72,0xe1,0x0f,0x10,0x03,0x61,0x75,0x74,0x6f,0xe0,0x02,0x3f,0x40,0x00,0x0e,0x77,0x69,0x64,0x74,0x68,0x3a,0x20,0x66,0x69,0x74,0x2d,0x63,0x6f,0x6e,0x74,0x20,0xe3,0xe0,0x06,0x20,0xe0,0x1f,0x81,0x01,0x62,0x75,
	0x21,0xcc,0x04,0x6e,0x23,0x70,0x6c,0x61,0xe1,0x10,0x8f,0xe0,0x11,0x7e,0x01,0x31,0x30,0xe0,0x09,0xfa,0x08,0x68,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x34,0xe0,0x05,0x1a,0xe0,0x02,0x72,0x00,0x74,0x23,0x41,0x0c,
	0x61,0x72,0x65,0x61,0x23,0x73,0x63,0x6f,0x72,0x65,0x20,0x7b,0x20,0xe0,0x01,0x1a,0x40,0x00,0xa0,0x5b,0x00,0x34,0xe0,0x12,0x5b,0xe0,0x0b,0x77,0xc2,0xd7,0x61,0x4c,0x02,0x3a,0x20,0x62,0x20,0x60,0x02,0x6b,0x2d,
	0x77,0x21,0xa9,0xe0,0x06,0x27,0x40,0x12,0x00,0x2d,0x60,0x1d,0xc0,0x24,0x02,0x61,0x6c,0x6c,0xe0,0x02,0x23,0xe0,0x02,0xa8,0x61,0x9c,0x00,0x2e,0x40,0xae,0xe1,0x07,0x1a,0xa0,0xa3,0x00,0x33,0xe0,0x05,0x86,0x20,
	0x3a,0x80,0x0c,0x01,0x3c,0x2f,0xe4,0x03,0x0a,0x0d,0x3c,0x73,0x63,0x72,0x69,0x70,0x74,0x20,0x74,0x79,0x70,0x65,0x3d,0x22,0x40,0x4e,0x04,0x2f,0x6a,0x61,0x76,0x61,0x80,0x15,0x00,0x22,0xa0,0x24,0x40,0x00,0x04,
	0x64,0x6f,0x63,0x75,0x6d,0x21,0xca,0x03,0x2e,0x24,0x28,0x22,0xe1,0x02,0x97,0x10,0x22,0x29,0x2e,0x6f,0x6e,0x63,0x6c,0x69,0x63,0x6b,0x20,0x3d,0x20,0x66,0x75,0x6e,0x63,0x41,0xd7,0x01,0x28,0x29,0xe0,0x07,0x93,
	0x06,0x76,0x61,0x72,0x20,0x6d,0x6f,0x64,0xe1,0x03,0xe7,0x40,0x00,0x03,0x69,0x66,0x20,0x28,0xe0,0x00,0x58,0x05,0x67,0x65,0x74,0x45,0x6c,0x65,0x40,0x0a,0x05,0x42,0x79,0x49,0x64,0x28,0x22,0x40,0x2f,0x00,0x31,
	0x20,0x5f,0x06,0x63,0x68,0x65,0x63,0x6b,0x65,0x64,0xe0,0x08,0x53,0x40,0x00,0x40,0x23,0x20,0x78,0x02,0x22,0x31,0x22,0xe0,0x06,0x59,0x04,0x7d,0x20,0x65,0x6c,0x73,0x21,0xbf,0xe0,0x05,0x15,0x40,0x00,0xc0,0x32,
	0x00,0x32,0xe0,0x08,0x32,0xe0,0x05,0x0e,0x40,0xb2,0x02,0x6b,0x65,0x79,0x20,0x2a,0xe0,0x10,0xa1,0x20,0x1e,0x20,0x9f,0x03,0x76,0x61,0x6c,0x75,0xe0,0x07,0xd8,0x40,0x3c,0x00,0x73,0x24,0xed,0x01,0x65,0x54,0x21,
	0x57,0xe0,0x13,0x42,0x60,0x24,0x00,0x2d,0x41,0x7d,0xe0,0x12,0x49,0x04,0x74,0x69,0x6d,0x65,0x53,0x25,0x35,0x07,0x61,0x74,0x75,0x72,0x65,0x4c,0x6f,0x77,0x23,0x8d,0xe0,0x12,0x52,0x40,0x2d,0x01,0x2d,0x73,0xc0,
	0x2e,0x00,0x2d,0x22,0x76,0x01,0x65,0x72,0xe0,0x12,0x5c,0x02,0x42,0x50,0x4d,0xe0,0x13,0x4d,0x02,0x62,0x70,0x6d,0xe0,0x12,0x3c,0x83,0x25,0xe0,0x12,0x3e,0x60,0x20,0xe0,0x0e,0x40,0x24,0x1c,0x00,0x73,0x22,0x79,
	0x08,0x68,0x69,0x73,0x57,0x69,0x6e,0x64,0x6f,0x77,0x20,0x47,0x80,0x08,0x00,0x2e,0x40,0x13,0xe0,0x06,0x2c,0x40,0x12,0xa0,0x1d,0x08,0x66,0x72,0x61,0x6d,0x65,0x2e,0x6f,0x75,0x74,0x23,0x01,0x00,0x28,0x41,0xce,
	0x00,0x2c,0x41,0xa8,0x00,0x2c,0x20,0x8c,0x21,0x4b,0x41,0x70,0x40,0x0a,0x20,0x76,0x00,0x2c,0xe1,0x0a,0x38,0x00,0x2c,0x40,0xef,0xe5,0x03,0x53,0xa1,0xf5,0x23,0x15,0x62,0xf2,0x22,0xf1,0x01,0x3c,0x2f,0xa7,0x58,
	0x00,0x3c,0x46,0x08,0x20,0x07,0x20,0x1e,0x0c,0x20,0x3c,0x64,0x69,0x76,0x20,0x63,0x6c,0x61,0x73,0x73,0x3d,0x22,0x40,0x16,0xe3,0x03,0x1a,0xe0,0x03,0x1b,0x63,0x96,0x63,0xe6,0x25,0x33,0xe0,0x03,0x24,0x40,0x00,
	0xe0,0x08,0x28,0x04,0x22,0x20,0x69,0x64,0x3d,0x62,0xe8,0xe0,0x07,0x2a,0x40,0x00,0x00,0x4d,0x20,0x17,0x00,0x3a,0xe0,0x09,0x16,0x00,0x3c,0x60,0x3a,0xa3,0xb1,0x45,0xe7,0x01,0x6f,0x22,0x21,0x8b,0x21,0x5e,0x00,
	0x3d,0x23,0x06,0xe0,0x00,0x50,0x20,0x0a,0xa3,0x38,0xe0,0x0a,0x59,0x0b,0x3c,0x6c,0x61,0x62,0x65,0x6c,0x20,0x66,0x6f,0x72,0x3d,0x22,0x48,0x08,0x02,0x22,0x3e,0x53,0x26,0xbe,0x09,0x6c,0x65,0x20,0x4e,0x6f,0x74,
	0x65,0x73,0x3c,0x2f,0x60,0x1e,0xe0,0x0b,0x37,0xe0,0x11,0x7a,0x00,0x32,0xe0,0x0b,0xc1,0xe0,0x09,0x67,0x01,0x43,0x68,0x24,0xe2,0x0b,0x20,0x50,0x72,0x6f,0x67,0x72,0x65,0x73,0x73,0x69,0x6f,0x6e,0xe0,0x0d,0x6c,
	0x01,0x3c,0x2f,0x21,0x2a,0xe0,0x07,0x13,0x20,0x12,0xe1,0x05,0x3d,0xe0,0x06,0x20,0x40,0x00,0x00,0x53,0x42,0x03,0xe1,0x11,0x34,0xa0,0x3e,0x44,0xe7,0x81,0x2a,0x22,0x38,0xe0,0x0b,0x46,0x06,0x3c,0x73,0x65,0x6c,
	0x65,0x63,0x74,0x60,0x22,0x62,0x56,0x83,0xa2,0xe0,0x0a,0x29,0x40,0x00,0x02,0x3c,0x6f,0x70,0x44,0xf6,0xc1,0x0a,0x03,0x6d,0x61,0x6a,0x6f,0x21,0xfb,0x00,0x4d,0x40,0x06,0x01,0x3c,0x2f,0x80,0x1b,0xe0,0x1e,0x39,
	0x01,0x69,0x6e,0x60,0x39,0x40,0x06,0xe0,0x12,0x39,0x22,0xac,0x60,0x9e,0xe0,0x06,0x1a,0xe1,0x30,0x34,0xe1,0x03,0xa6,0x43,0x32,0xe4,0x01,0x3d,0x02,0x22,0x3e,0x54,0x20,0x0f,0x00,0x20,0xe0,0x00,0x0f,0x00,0x3a,
	0x20,0x64,0x60,0x2c,0xe0,0x0b,0x45,0x60,0x5f,0xc0,0x6c,0xe1,0x01,0x62,0xe0,0x05,0x51,0x01,0x2d,0x75,0xe3,0x0b,0x19,0x40,0x00,0x00,0x2f,0xe0,0x09,0x12,0xe0,0x1e,0x52,0x84,0xe2,0xe0,0x06,0x52,0xe1,0x3c,0x0d,
	0x00,0x62,0x24,0xfd,0x00,0x3e,0x24,0x31,0xe0,0x2b,0xf7,0x60,0x3b,0xe0,0x05,0x2e,0xe0,0x31,0x93,0x40,0x24,0x60,0x91,0x64,0xd9,0x04,0x22,0x3e,0x59,0x6f,0x75,0xa5,0x7d,0x40,0x9a,0x20,0x1d,0xe0,0x0b,0x34,0x40,
	0x8b,0x48,0xcc,0x60,0x8e,0x60,0x2c,0x01,0x22,0x3e,0x2c,0x16,0xa0,0x15,0xe0,0x06,0x31,0xe0,0x0b,0x45,0x00,0x3c,0x87,0xe9,0x60,0x3f,0x67,0xed,0x01,0x3e,0x50,0x20,0x05,0x01,0x3c,0x2f,0x80,0x16,0xe0,0x02,0x2c,
	0xe0,0x03,0x3c,0xc0,0x0b,0x20,0x26,0x25,0x28,0x60,0x08,0x23,0xfb,0x01,0x6c,0x3e,
};
