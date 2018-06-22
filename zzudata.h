#pragma once
static unsigned char start_packet[] = {
	0x01, 0xd0, 0xf8, 0x00, 0x00, 0x03, 0xa0, 0x8c,
	0xfd, 0x31, 0x1e, 0xfa, 0x88, 0x8e, 0x01, 0x01,
	0x00, 0x00, 0xff, 0xff, 0x37, 0x77, 0xff, 0xaf,
	0xd9, 0xf8, 0xef, 0x00, 0x00, 0x00, 0xff, 0xaf,
	0xd9, 0xf8, 0x7f, 0x01, 0xff, 0xff, 0x53, 0xcf,
	0x44, 0x00, 0x00, 0x13, 0x11, 0x38, 0x30, 0x32,
	0x31, 0x78, 0x2e, 0x65, 0x78, 0x65, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0x01,
	0x02, 0x00, 0x00, 0x00, 0x13, 0x11, 0x01, 0xb4,
	0x1a, 0x0c, 0x00, 0x00, 0x13, 0x11, 0x18, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x1a, 0x0e, 0x00, 0x00,
	0x13, 0x11, 0x2d, 0x08, 0xa0, 0x8c, 0xfd, 0x31,
	0x1e, 0xfa, 0x1a, 0x08, 0x00, 0x00, 0x13, 0x11,
	0x2f, 0x02, 0x1a, 0x08, 0x00, 0x00, 0x13, 0x11,
	0x76, 0x02, 0x1a, 0x09, 0x00, 0x00, 0x13, 0x11,
	0x35, 0x03, 0x01, 0x1a, 0x18, 0x00, 0x00, 0x13,
	0x11, 0x36, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x18, 0x00, 0x00, 0x13,
	0x11, 0x38, 0x12, 0xfe, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x8c, 0x9a, 0xef, 0x36, 0x68,
	0x23, 0xee, 0x03, 0x1a, 0x18, 0x00, 0x00, 0x13,
	0x11, 0x4e, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x88, 0x00, 0x00, 0x13,
	0x11, 0x4d, 0x82, 0x63, 0x65, 0x64, 0x66, 0x65,
	0x62, 0x31, 0x64, 0x37, 0x66, 0x37, 0x31, 0x34,
	0x35, 0x34, 0x36, 0x65, 0x35, 0x37, 0x63, 0x61,
	0x32, 0x33, 0x62, 0x35, 0x36, 0x65, 0x31, 0x38,
	0x38, 0x38, 0x62, 0x31, 0x63, 0x35, 0x37, 0x36,
	0x37, 0x38, 0x30, 0x62, 0x36, 0x38, 0x64, 0x61,
	0x32, 0x37, 0x36, 0x34, 0x62, 0x32, 0x64, 0x61,
	0x39, 0x62, 0x61, 0x64, 0x66, 0x36, 0x38, 0x66,
	0x65, 0x37, 0x39, 0x31, 0x33, 0x30, 0x37, 0x34,
	0x30, 0x39, 0x37, 0x35, 0x39, 0x36, 0x35, 0x32,
	0x33, 0x32, 0x63, 0x35, 0x61, 0x35, 0x65, 0x33,
	0x36, 0x62, 0x30, 0x30, 0x63, 0x30, 0x39, 0x34,
	0x30, 0x31, 0x64, 0x30, 0x66, 0x64, 0x38, 0x31,
	0x31, 0x37, 0x39, 0x61, 0x33, 0x31, 0x38, 0x62,
	0x36, 0x36, 0x35, 0x38, 0x37, 0x66, 0x66, 0x39,
	0x65, 0x34, 0x39, 0x61, 0x61, 0x39, 0x38, 0x66,
	0x35, 0x64, 0x30, 0x1a, 0x28, 0x00, 0x00, 0x13,
	0x11, 0x39, 0x22, 0x64, 0x65, 0x66, 0x61, 0x75,
	0x6c, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x48, 0x00, 0x00, 0x13,
	0x11, 0x54, 0x42, 0x4a, 0x52, 0x31, 0x30, 0x30,
	0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x08, 0x00, 0x00, 0x13,
	0x11, 0x55, 0x02, 0x1a, 0x09, 0x00, 0x00, 0x13,
	0x11, 0x62, 0x03, 0x00, 0x1a, 0x09, 0x00, 0x00,
	0x13, 0x11, 0x70, 0x03, 0x40, 0x1a, 0x1e, 0x00,
	0x00, 0x13, 0x11, 0x6f, 0x18, 0x52, 0x47, 0x2d,
	0x53, 0x55, 0x20, 0x46, 0x6f, 0x72, 0x20, 0x4c,
	0x69, 0x6e, 0x75, 0x78, 0x20, 0x56, 0x31, 0x2e,
	0x33, 0x30, 0x00, 0x1a, 0x09, 0x00, 0x00, 0x13,
	0x11, 0x79, 0x03, 0x02
};
static unsigned char identify_packet[540]=
{
	0x00, 0x1a, 0xa9, 0x17, 0xff, 0xff, 0xa0, 0x8c,
	0xfd, 0x31, 0x1e, 0xfa, 0x88, 0x8e, 0x01, 0x00,
	0x00, 0x10, 0x02, 0x01, 0x00, 0x10, 0x01, 0x32,
	0x30, 0x31, 0x36, 0x32, 0x34, 0x33, 0x30, 0x32,
	0x33, 0x37, 0xff, 0xff, 0x37, 0x77, 0xff, 0xaf,
	0xd9, 0xf8, 0xef, 0x00, 0x00, 0x00, 0xff, 0xaf,
	0xd9, 0xf8, 0x7f, 0x01, 0xff, 0xff, 0x53, 0xcf,
	0x44, 0x00, 0x00, 0x13, 0x11, 0x38, 0x30, 0x32,
	0x31, 0x78, 0x2e, 0x65, 0x78, 0x65, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0x01,
	0x02, 0xd0, 0x00, 0x00, 0x13, 0x11, 0x01, 0xb4,
	0x1a, 0x0c, 0x00, 0x00, 0x13, 0x11, 0x18, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x1a, 0x0e, 0x00, 0x00,
	0x13, 0x11, 0x2d, 0x08, 0xa0, 0x8c, 0xfd, 0x31,
	0x1e, 0xfa, 0x1a, 0x08, 0x00, 0x00, 0x13, 0x11,
	0x2f, 0x02, 0x1a, 0x08, 0x00, 0x00, 0x13, 0x11,
	0x76, 0x02, 0x1a, 0x09, 0x00, 0x00, 0x13, 0x11,
	0x35, 0x03, 0x01, 0x1a, 0x18, 0x00, 0x00, 0x13,
	0x11, 0x36, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x18, 0x00, 0x00, 0x13,
	0x11, 0x38, 0x12, 0xfe, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x8c, 0x9a, 0xef, 0x36, 0x68,
	0x23, 0xee, 0x03, 0x1a, 0x18, 0x00, 0x00, 0x13,
	0x11, 0x4e, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x88, 0x00, 0x00, 0x13,
	0x11, 0x4d, 0x82, 0x63, 0x65, 0x64, 0x66, 0x65,
	0x62, 0x31, 0x64, 0x37, 0x66, 0x37, 0x31, 0x34,
	0x35, 0x34, 0x36, 0x65, 0x35, 0x37, 0x63, 0x61,
	0x32, 0x33, 0x62, 0x35, 0x36, 0x65, 0x31, 0x38,
	0x38, 0x38, 0x62, 0x31, 0x63, 0x35, 0x37, 0x36,
	0x37, 0x38, 0x30, 0x62, 0x36, 0x38, 0x64, 0x61,
	0x32, 0x37, 0x36, 0x34, 0x62, 0x32, 0x64, 0x61,
	0x39, 0x62, 0x61, 0x64, 0x66, 0x36, 0x38, 0x66,
	0x65, 0x37, 0x39, 0x31, 0x33, 0x30, 0x37, 0x34,
	0x30, 0x39, 0x37, 0x35, 0x39, 0x36, 0x35, 0x32,
	0x33, 0x32, 0x63, 0x35, 0x61, 0x35, 0x65, 0x33,
	0x36, 0x62, 0x30, 0x30, 0x63, 0x30, 0x39, 0x34,
	0x30, 0x31, 0x64, 0x30, 0x66, 0x64, 0x38, 0x31,
	0x31, 0x37, 0x39, 0x61, 0x33, 0x31, 0x38, 0x62,
	0x36, 0x36, 0x35, 0x38, 0x37, 0x66, 0x66, 0x39,
	0x65, 0x34, 0x39, 0x61, 0x61, 0x39, 0x38, 0x66,
	0x35, 0x64, 0x30, 0x1a, 0x28, 0x00, 0x00, 0x13,
	0x11, 0x39, 0x22, 0x64, 0x65, 0x66, 0x61, 0x75,
	0x6c, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x48, 0x00, 0x00, 0x13,
	0x11, 0x54, 0x42, 0x4a, 0x52, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1a, 0x08, 0x00, 0x00, 0x13,
	0x11, 0x55, 0x02, 0x1a, 0x09, 0x00, 0x00, 0x13,
	0x11, 0x62, 0x03, 0x00, 0x1a, 0x09, 0x00, 0x00,
	0x13, 0x11, 0x70, 0x03, 0x40, 0x1a, 0x1e, 0x00,
	0x00, 0x13, 0x11, 0x6f, 0x18, 0x52, 0x47, 0x2d,
	0x53, 0x55, 0x20, 0x46, 0x6f, 0x72, 0x20, 0x4c,
	0x69, 0x6e, 0x75, 0x78, 0x20, 0x56, 0x31, 0x2e,
	0x33, 0x30, 0x00, 0x1a, 0x09, 0x00, 0x00, 0x13,
	0x11, 0x79, 0x03, 0x02
};
static unsigned char md5challenge_packet[573]
{
	0x00, 0x1a, 0xa9, 0x17, 0xff, 0xff, 0xa0, 0x8c,
	0xfd, 0x31, 0x1e, 0xfa, 0x88, 0x8e, 0x01, 0x00,
	0x00, 0x21, 0x02, 0x02, 0x00, 0x21, 0x04, 0x10,
	0x8a, 0x81, 0x26, 0x87, 0xb2, 0x82, 0x48, 0xa0,
	0x0d, 0x3d, 0x0b, 0x41, 0x4b, 0x9b, 0x5a, 0x0d,
	0x32, 0x30, 0x31, 0x36, 0x32, 0x34, 0x33, 0x30,
	0x32, 0x33, 0x37, 0xff, 0xff, 0x37, 0x77, 0xff,
	0xaf, 0xd9, 0xf8, 0xef, 0x00, 0x00, 0x00, 0xff,
	0xaf, 0xd9, 0xf8, 0x7f, 0x01, 0xff, 0xff, 0x53,
	0xcf, 0x44, 0x00, 0x00, 0x13, 0x11, 0x38, 0x30,
	0x32, 0x31, 0x78, 0x2e, 0x65, 0x78, 0x65, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e,
	0x01, 0x02, 0xd0, 0x00, 0x00, 0x13, 0x11, 0x01,
	0xc4, 0x1a, 0x0c, 0x00, 0x00, 0x13, 0x11, 0x18,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x0e, 0x00,
	0x00, 0x13, 0x11, 0x2d, 0x08, 0xa0, 0x8c, 0xfd,
	0x31, 0x1e, 0xfa, 0x1a, 0x18, 0x00, 0x00, 0x13,
	0x11, 0x2f, 0x12, 0x5e, 0xfe, 0xb5, 0x4a, 0xc9,
	0x9c, 0xd3, 0x32, 0xca, 0x36, 0x15, 0xd2, 0x13,
	0x43, 0x9c, 0xc8, 0x1a, 0x08, 0x00, 0x00, 0x13,
	0x11, 0x76, 0x02, 0x1a, 0x09, 0x00, 0x00, 0x13,
	0x11, 0x35, 0x03, 0x01, 0x1a, 0x18, 0x00, 0x00,
	0x13, 0x11, 0x36, 0x12, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x1a, 0x18, 0x00, 0x00,
	0x13, 0x11, 0x38, 0x12, 0xfe, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x8c, 0x9a, 0xef, 0x36,
	0x68, 0x23, 0xee, 0x03, 0x1a, 0x18, 0x00, 0x00,
	0x13, 0x11, 0x4e, 0x12, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x1a, 0x88, 0x00, 0x00,
	0x13, 0x11, 0x4d, 0x82, 0x32, 0x39, 0x31, 0x31,
	0x38, 0x36, 0x38, 0x65, 0x63, 0x39, 0x65, 0x36,
	0x66, 0x34, 0x38, 0x30, 0x61, 0x39, 0x34, 0x65,
	0x64, 0x39, 0x38, 0x64, 0x32, 0x63, 0x37, 0x33,
	0x35, 0x64, 0x37, 0x62, 0x33, 0x35, 0x35, 0x64,
	0x62, 0x65, 0x31, 0x37, 0x39, 0x36, 0x64, 0x63,
	0x63, 0x35, 0x36, 0x64, 0x37, 0x34, 0x64, 0x34,
	0x38, 0x32, 0x66, 0x35, 0x33, 0x33, 0x64, 0x30,
	0x63, 0x39, 0x31, 0x31, 0x30, 0x30, 0x64, 0x65,
	0x38, 0x32, 0x39, 0x33, 0x66, 0x30, 0x61, 0x64,
	0x33, 0x63, 0x62, 0x38, 0x34, 0x66, 0x38, 0x35,
	0x32, 0x66, 0x61, 0x31, 0x35, 0x35, 0x64, 0x65,
	0x31, 0x31, 0x39, 0x61, 0x38, 0x66, 0x65, 0x32,
	0x65, 0x63, 0x66, 0x36, 0x62, 0x39, 0x61, 0x33,
	0x38, 0x63, 0x31, 0x36, 0x61, 0x39, 0x36, 0x33,
	0x32, 0x34, 0x30, 0x65, 0x64, 0x30, 0x35, 0x31,
	0x66, 0x64, 0x38, 0x64, 0x1a, 0x28, 0x00, 0x00,
	0x13, 0x11, 0x39, 0x22, 0x64, 0x65, 0x66, 0x61,
	0x75, 0x6c, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x1a, 0x48, 0x00, 0x00,
	0x13, 0x11, 0x54, 0x42, 0x4a, 0x52, 0x31, 0x30,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x1a, 0x08, 0x00, 0x00,
	0x13, 0x11, 0x55, 0x02, 0x1a, 0x09, 0x00, 0x00,
	0x13, 0x11, 0x62, 0x03, 0x00, 0x1a, 0x09, 0x00,
	0x00, 0x13, 0x11, 0x70, 0x03, 0x40, 0x1a, 0x1e,
	0x00, 0x00, 0x13, 0x11, 0x6f, 0x18, 0x52, 0x47,
	0x2d, 0x53, 0x55, 0x20, 0x46, 0x6f, 0x72, 0x20,
	0x4c, 0x69, 0x6e, 0x75, 0x78, 0x20, 0x56, 0x31,
	0x2e, 0x33, 0x30, 0x00, 0x1a, 0x09, 0x00, 0x00,
	0x13, 0x11, 0x79, 0x03, 0x02
};