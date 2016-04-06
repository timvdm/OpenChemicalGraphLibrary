template<typename Graph>
Graph nanotube_9n_9m_40A()
{
  Graph g;

  for (int i = 0; i < 594; ++i)
    ocgl::addVertex(g);

  std::vector<std::pair<unsigned int, unsigned int>> edges;
  edges.push_back(std::make_pair(0, 1));
  edges.push_back(std::make_pair(0, 35));
  edges.push_back(std::make_pair(1, 2));
  edges.push_back(std::make_pair(2, 3));
  edges.push_back(std::make_pair(2, 37));
  edges.push_back(std::make_pair(3, 40));
  edges.push_back(std::make_pair(4, 3));
  edges.push_back(std::make_pair(5, 4));
  edges.push_back(std::make_pair(5, 6));
  edges.push_back(std::make_pair(6, 41));
  edges.push_back(std::make_pair(7, 6));
  edges.push_back(std::make_pair(7, 44));
  edges.push_back(std::make_pair(8, 7));
  edges.push_back(std::make_pair(9, 8));
  edges.push_back(std::make_pair(9, 10));
  edges.push_back(std::make_pair(10, 11));
  edges.push_back(std::make_pair(10, 45));
  edges.push_back(std::make_pair(11, 48));
  edges.push_back(std::make_pair(12, 11));
  edges.push_back(std::make_pair(13, 12));
  edges.push_back(std::make_pair(13, 14));
  edges.push_back(std::make_pair(14, 15));
  edges.push_back(std::make_pair(14, 49));
  edges.push_back(std::make_pair(15, 52));
  edges.push_back(std::make_pair(16, 15));
  edges.push_back(std::make_pair(17, 16));
  edges.push_back(std::make_pair(17, 18));
  edges.push_back(std::make_pair(18, 19));
  edges.push_back(std::make_pair(18, 53));
  edges.push_back(std::make_pair(19, 56));
  edges.push_back(std::make_pair(20, 19));
  edges.push_back(std::make_pair(21, 20));
  edges.push_back(std::make_pair(21, 22));
  edges.push_back(std::make_pair(22, 57));
  edges.push_back(std::make_pair(23, 22));
  edges.push_back(std::make_pair(23, 60));
  edges.push_back(std::make_pair(24, 23));
  edges.push_back(std::make_pair(25, 24));
  edges.push_back(std::make_pair(25, 26));
  edges.push_back(std::make_pair(26, 27));
  edges.push_back(std::make_pair(26, 61));
  edges.push_back(std::make_pair(27, 64));
  edges.push_back(std::make_pair(28, 27));
  edges.push_back(std::make_pair(29, 28));
  edges.push_back(std::make_pair(29, 30));
  edges.push_back(std::make_pair(30, 65));
  edges.push_back(std::make_pair(31, 30));
  edges.push_back(std::make_pair(31, 68));
  edges.push_back(std::make_pair(32, 33));
  edges.push_back(std::make_pair(32, 31));
  edges.push_back(std::make_pair(33, 34));
  edges.push_back(std::make_pair(34, 35));
  edges.push_back(std::make_pair(34, 69));
  edges.push_back(std::make_pair(35, 36));
  edges.push_back(std::make_pair(36, 71));
  edges.push_back(std::make_pair(37, 36));
  edges.push_back(std::make_pair(37, 38));
  edges.push_back(std::make_pair(38, 39));
  edges.push_back(std::make_pair(38, 73));
  edges.push_back(std::make_pair(39, 76));
  edges.push_back(std::make_pair(40, 39));
  edges.push_back(std::make_pair(41, 40));
  edges.push_back(std::make_pair(41, 42));
  edges.push_back(std::make_pair(42, 77));
  edges.push_back(std::make_pair(43, 42));
  edges.push_back(std::make_pair(43, 80));
  edges.push_back(std::make_pair(44, 43));
  edges.push_back(std::make_pair(45, 44));
  edges.push_back(std::make_pair(45, 46));
  edges.push_back(std::make_pair(46, 81));
  edges.push_back(std::make_pair(47, 46));
  edges.push_back(std::make_pair(47, 84));
  edges.push_back(std::make_pair(48, 47));
  edges.push_back(std::make_pair(49, 48));
  edges.push_back(std::make_pair(49, 50));
  edges.push_back(std::make_pair(50, 51));
  edges.push_back(std::make_pair(50, 85));
  edges.push_back(std::make_pair(51, 88));
  edges.push_back(std::make_pair(52, 51));
  edges.push_back(std::make_pair(53, 52));
  edges.push_back(std::make_pair(53, 54));
  edges.push_back(std::make_pair(54, 55));
  edges.push_back(std::make_pair(54, 89));
  edges.push_back(std::make_pair(55, 92));
  edges.push_back(std::make_pair(56, 55));
  edges.push_back(std::make_pair(57, 56));
  edges.push_back(std::make_pair(57, 58));
  edges.push_back(std::make_pair(58, 59));
  edges.push_back(std::make_pair(58, 93));
  edges.push_back(std::make_pair(59, 96));
  edges.push_back(std::make_pair(60, 61));
  edges.push_back(std::make_pair(60, 59));
  edges.push_back(std::make_pair(61, 62));
  edges.push_back(std::make_pair(62, 97));
  edges.push_back(std::make_pair(63, 62));
  edges.push_back(std::make_pair(63, 100));
  edges.push_back(std::make_pair(64, 65));
  edges.push_back(std::make_pair(64, 63));
  edges.push_back(std::make_pair(65, 66));
  edges.push_back(std::make_pair(66, 101));
  edges.push_back(std::make_pair(67, 66));
  edges.push_back(std::make_pair(67, 104));
  edges.push_back(std::make_pair(68, 69));
  edges.push_back(std::make_pair(68, 67));
  edges.push_back(std::make_pair(69, 70));
  edges.push_back(std::make_pair(70, 105));
  edges.push_back(std::make_pair(71, 70));
  edges.push_back(std::make_pair(71, 72));
  edges.push_back(std::make_pair(72, 107));
  edges.push_back(std::make_pair(73, 72));
  edges.push_back(std::make_pair(73, 74));
  edges.push_back(std::make_pair(74, 75));
  edges.push_back(std::make_pair(74, 109));
  edges.push_back(std::make_pair(75, 112));
  edges.push_back(std::make_pair(76, 77));
  edges.push_back(std::make_pair(76, 75));
  edges.push_back(std::make_pair(77, 78));
  edges.push_back(std::make_pair(78, 79));
  edges.push_back(std::make_pair(78, 113));
  edges.push_back(std::make_pair(79, 116));
  edges.push_back(std::make_pair(80, 79));
  edges.push_back(std::make_pair(81, 80));
  edges.push_back(std::make_pair(81, 82));
  edges.push_back(std::make_pair(82, 83));
  edges.push_back(std::make_pair(82, 117));
  edges.push_back(std::make_pair(83, 120));
  edges.push_back(std::make_pair(84, 85));
  edges.push_back(std::make_pair(84, 83));
  edges.push_back(std::make_pair(85, 86));
  edges.push_back(std::make_pair(86, 121));
  edges.push_back(std::make_pair(87, 86));
  edges.push_back(std::make_pair(87, 124));
  edges.push_back(std::make_pair(88, 89));
  edges.push_back(std::make_pair(88, 87));
  edges.push_back(std::make_pair(89, 90));
  edges.push_back(std::make_pair(90, 125));
  edges.push_back(std::make_pair(91, 90));
  edges.push_back(std::make_pair(91, 128));
  edges.push_back(std::make_pair(92, 93));
  edges.push_back(std::make_pair(92, 91));
  edges.push_back(std::make_pair(93, 94));
  edges.push_back(std::make_pair(94, 129));
  edges.push_back(std::make_pair(95, 94));
  edges.push_back(std::make_pair(95, 132));
  edges.push_back(std::make_pair(96, 97));
  edges.push_back(std::make_pair(96, 95));
  edges.push_back(std::make_pair(97, 98));
  edges.push_back(std::make_pair(98, 133));
  edges.push_back(std::make_pair(99, 98));
  edges.push_back(std::make_pair(99, 136));
  edges.push_back(std::make_pair(100, 101));
  edges.push_back(std::make_pair(100, 99));
  edges.push_back(std::make_pair(101, 102));
  edges.push_back(std::make_pair(102, 137));
  edges.push_back(std::make_pair(103, 102));
  edges.push_back(std::make_pair(103, 140));
  edges.push_back(std::make_pair(104, 105));
  edges.push_back(std::make_pair(104, 103));
  edges.push_back(std::make_pair(105, 106));
  edges.push_back(std::make_pair(106, 141));
  edges.push_back(std::make_pair(107, 106));
  edges.push_back(std::make_pair(107, 108));
  edges.push_back(std::make_pair(108, 143));
  edges.push_back(std::make_pair(109, 108));
  edges.push_back(std::make_pair(109, 110));
  edges.push_back(std::make_pair(110, 111));
  edges.push_back(std::make_pair(110, 145));
  edges.push_back(std::make_pair(111, 148));
  edges.push_back(std::make_pair(112, 111));
  edges.push_back(std::make_pair(113, 112));
  edges.push_back(std::make_pair(113, 114));
  edges.push_back(std::make_pair(114, 115));
  edges.push_back(std::make_pair(114, 149));
  edges.push_back(std::make_pair(115, 152));
  edges.push_back(std::make_pair(116, 115));
  edges.push_back(std::make_pair(117, 116));
  edges.push_back(std::make_pair(117, 118));
  edges.push_back(std::make_pair(118, 119));
  edges.push_back(std::make_pair(118, 153));
  edges.push_back(std::make_pair(119, 156));
  edges.push_back(std::make_pair(120, 119));
  edges.push_back(std::make_pair(121, 120));
  edges.push_back(std::make_pair(121, 122));
  edges.push_back(std::make_pair(122, 157));
  edges.push_back(std::make_pair(123, 122));
  edges.push_back(std::make_pair(123, 160));
  edges.push_back(std::make_pair(124, 123));
  edges.push_back(std::make_pair(125, 124));
  edges.push_back(std::make_pair(125, 126));
  edges.push_back(std::make_pair(126, 161));
  edges.push_back(std::make_pair(127, 126));
  edges.push_back(std::make_pair(127, 164));
  edges.push_back(std::make_pair(128, 129));
  edges.push_back(std::make_pair(128, 127));
  edges.push_back(std::make_pair(129, 130));
  edges.push_back(std::make_pair(130, 165));
  edges.push_back(std::make_pair(131, 130));
  edges.push_back(std::make_pair(131, 168));
  edges.push_back(std::make_pair(132, 133));
  edges.push_back(std::make_pair(132, 131));
  edges.push_back(std::make_pair(133, 134));
  edges.push_back(std::make_pair(134, 169));
  edges.push_back(std::make_pair(135, 134));
  edges.push_back(std::make_pair(135, 172));
  edges.push_back(std::make_pair(136, 137));
  edges.push_back(std::make_pair(136, 135));
  edges.push_back(std::make_pair(137, 138));
  edges.push_back(std::make_pair(138, 173));
  edges.push_back(std::make_pair(139, 138));
  edges.push_back(std::make_pair(139, 176));
  edges.push_back(std::make_pair(140, 141));
  edges.push_back(std::make_pair(140, 139));
  edges.push_back(std::make_pair(141, 142));
  edges.push_back(std::make_pair(142, 177));
  edges.push_back(std::make_pair(143, 142));
  edges.push_back(std::make_pair(143, 144));
  edges.push_back(std::make_pair(144, 179));
  edges.push_back(std::make_pair(145, 144));
  edges.push_back(std::make_pair(145, 146));
  edges.push_back(std::make_pair(146, 147));
  edges.push_back(std::make_pair(146, 181));
  edges.push_back(std::make_pair(147, 184));
  edges.push_back(std::make_pair(148, 147));
  edges.push_back(std::make_pair(149, 148));
  edges.push_back(std::make_pair(149, 150));
  edges.push_back(std::make_pair(150, 151));
  edges.push_back(std::make_pair(150, 185));
  edges.push_back(std::make_pair(151, 188));
  edges.push_back(std::make_pair(152, 151));
  edges.push_back(std::make_pair(153, 152));
  edges.push_back(std::make_pair(153, 154));
  edges.push_back(std::make_pair(154, 155));
  edges.push_back(std::make_pair(154, 189));
  edges.push_back(std::make_pair(155, 192));
  edges.push_back(std::make_pair(156, 155));
  edges.push_back(std::make_pair(157, 156));
  edges.push_back(std::make_pair(157, 158));
  edges.push_back(std::make_pair(158, 159));
  edges.push_back(std::make_pair(158, 193));
  edges.push_back(std::make_pair(159, 196));
  edges.push_back(std::make_pair(160, 159));
  edges.push_back(std::make_pair(161, 160));
  edges.push_back(std::make_pair(161, 162));
  edges.push_back(std::make_pair(162, 163));
  edges.push_back(std::make_pair(162, 197));
  edges.push_back(std::make_pair(163, 200));
  edges.push_back(std::make_pair(164, 163));
  edges.push_back(std::make_pair(165, 164));
  edges.push_back(std::make_pair(165, 166));
  edges.push_back(std::make_pair(166, 167));
  edges.push_back(std::make_pair(166, 201));
  edges.push_back(std::make_pair(167, 204));
  edges.push_back(std::make_pair(168, 169));
  edges.push_back(std::make_pair(168, 167));
  edges.push_back(std::make_pair(169, 170));
  edges.push_back(std::make_pair(170, 205));
  edges.push_back(std::make_pair(171, 170));
  edges.push_back(std::make_pair(171, 208));
  edges.push_back(std::make_pair(172, 173));
  edges.push_back(std::make_pair(172, 171));
  edges.push_back(std::make_pair(173, 174));
  edges.push_back(std::make_pair(174, 209));
  edges.push_back(std::make_pair(175, 174));
  edges.push_back(std::make_pair(175, 212));
  edges.push_back(std::make_pair(176, 177));
  edges.push_back(std::make_pair(176, 175));
  edges.push_back(std::make_pair(177, 178));
  edges.push_back(std::make_pair(178, 179));
  edges.push_back(std::make_pair(178, 213));
  edges.push_back(std::make_pair(179, 180));
  edges.push_back(std::make_pair(180, 181));
  edges.push_back(std::make_pair(180, 215));
  edges.push_back(std::make_pair(181, 182));
  edges.push_back(std::make_pair(182, 217));
  edges.push_back(std::make_pair(183, 182));
  edges.push_back(std::make_pair(183, 220));
  edges.push_back(std::make_pair(184, 185));
  edges.push_back(std::make_pair(184, 183));
  edges.push_back(std::make_pair(185, 186));
  edges.push_back(std::make_pair(186, 221));
  edges.push_back(std::make_pair(187, 186));
  edges.push_back(std::make_pair(187, 224));
  edges.push_back(std::make_pair(188, 187));
  edges.push_back(std::make_pair(189, 188));
  edges.push_back(std::make_pair(189, 190));
  edges.push_back(std::make_pair(190, 225));
  edges.push_back(std::make_pair(191, 190));
  edges.push_back(std::make_pair(191, 228));
  edges.push_back(std::make_pair(192, 191));
  edges.push_back(std::make_pair(193, 192));
  edges.push_back(std::make_pair(193, 194));
  edges.push_back(std::make_pair(194, 229));
  edges.push_back(std::make_pair(195, 194));
  edges.push_back(std::make_pair(195, 232));
  edges.push_back(std::make_pair(196, 195));
  edges.push_back(std::make_pair(197, 196));
  edges.push_back(std::make_pair(197, 198));
  edges.push_back(std::make_pair(198, 233));
  edges.push_back(std::make_pair(199, 198));
  edges.push_back(std::make_pair(199, 236));
  edges.push_back(std::make_pair(200, 199));
  edges.push_back(std::make_pair(201, 200));
  edges.push_back(std::make_pair(201, 202));
  edges.push_back(std::make_pair(202, 237));
  edges.push_back(std::make_pair(203, 202));
  edges.push_back(std::make_pair(203, 240));
  edges.push_back(std::make_pair(204, 203));
  edges.push_back(std::make_pair(205, 204));
  edges.push_back(std::make_pair(205, 206));
  edges.push_back(std::make_pair(206, 241));
  edges.push_back(std::make_pair(207, 206));
  edges.push_back(std::make_pair(207, 244));
  edges.push_back(std::make_pair(208, 209));
  edges.push_back(std::make_pair(208, 207));
  edges.push_back(std::make_pair(209, 210));
  edges.push_back(std::make_pair(210, 211));
  edges.push_back(std::make_pair(210, 245));
  edges.push_back(std::make_pair(211, 248));
  edges.push_back(std::make_pair(212, 213));
  edges.push_back(std::make_pair(212, 211));
  edges.push_back(std::make_pair(213, 214));
  edges.push_back(std::make_pair(214, 215));
  edges.push_back(std::make_pair(214, 249));
  edges.push_back(std::make_pair(215, 216));
  edges.push_back(std::make_pair(216, 251));
  edges.push_back(std::make_pair(217, 216));
  edges.push_back(std::make_pair(217, 218));
  edges.push_back(std::make_pair(218, 219));
  edges.push_back(std::make_pair(218, 253));
  edges.push_back(std::make_pair(219, 256));
  edges.push_back(std::make_pair(220, 219));
  edges.push_back(std::make_pair(221, 220));
  edges.push_back(std::make_pair(221, 222));
  edges.push_back(std::make_pair(222, 257));
  edges.push_back(std::make_pair(223, 222));
  edges.push_back(std::make_pair(223, 260));
  edges.push_back(std::make_pair(224, 223));
  edges.push_back(std::make_pair(225, 224));
  edges.push_back(std::make_pair(225, 226));
  edges.push_back(std::make_pair(226, 261));
  edges.push_back(std::make_pair(227, 226));
  edges.push_back(std::make_pair(227, 264));
  edges.push_back(std::make_pair(228, 229));
  edges.push_back(std::make_pair(228, 227));
  edges.push_back(std::make_pair(229, 230));
  edges.push_back(std::make_pair(230, 265));
  edges.push_back(std::make_pair(231, 230));
  edges.push_back(std::make_pair(231, 268));
  edges.push_back(std::make_pair(232, 233));
  edges.push_back(std::make_pair(232, 231));
  edges.push_back(std::make_pair(233, 234));
  edges.push_back(std::make_pair(234, 269));
  edges.push_back(std::make_pair(235, 234));
  edges.push_back(std::make_pair(235, 272));
  edges.push_back(std::make_pair(236, 235));
  edges.push_back(std::make_pair(237, 236));
  edges.push_back(std::make_pair(237, 238));
  edges.push_back(std::make_pair(238, 273));
  edges.push_back(std::make_pair(239, 238));
  edges.push_back(std::make_pair(239, 276));
  edges.push_back(std::make_pair(240, 239));
  edges.push_back(std::make_pair(241, 240));
  edges.push_back(std::make_pair(241, 242));
  edges.push_back(std::make_pair(242, 277));
  edges.push_back(std::make_pair(243, 242));
  edges.push_back(std::make_pair(243, 280));
  edges.push_back(std::make_pair(244, 245));
  edges.push_back(std::make_pair(244, 243));
  edges.push_back(std::make_pair(245, 246));
  edges.push_back(std::make_pair(246, 281));
  edges.push_back(std::make_pair(247, 246));
  edges.push_back(std::make_pair(247, 284));
  edges.push_back(std::make_pair(248, 249));
  edges.push_back(std::make_pair(248, 247));
  edges.push_back(std::make_pair(249, 250));
  edges.push_back(std::make_pair(250, 285));
  edges.push_back(std::make_pair(251, 250));
  edges.push_back(std::make_pair(251, 252));
  edges.push_back(std::make_pair(252, 287));
  edges.push_back(std::make_pair(253, 252));
  edges.push_back(std::make_pair(253, 254));
  edges.push_back(std::make_pair(254, 255));
  edges.push_back(std::make_pair(254, 289));
  edges.push_back(std::make_pair(255, 292));
  edges.push_back(std::make_pair(256, 257));
  edges.push_back(std::make_pair(256, 255));
  edges.push_back(std::make_pair(257, 258));
  edges.push_back(std::make_pair(258, 259));
  edges.push_back(std::make_pair(258, 293));
  edges.push_back(std::make_pair(259, 296));
  edges.push_back(std::make_pair(260, 259));
  edges.push_back(std::make_pair(261, 260));
  edges.push_back(std::make_pair(261, 262));
  edges.push_back(std::make_pair(262, 263));
  edges.push_back(std::make_pair(262, 297));
  edges.push_back(std::make_pair(263, 300));
  edges.push_back(std::make_pair(264, 263));
  edges.push_back(std::make_pair(265, 264));
  edges.push_back(std::make_pair(265, 266));
  edges.push_back(std::make_pair(266, 301));
  edges.push_back(std::make_pair(267, 266));
  edges.push_back(std::make_pair(267, 304));
  edges.push_back(std::make_pair(268, 267));
  edges.push_back(std::make_pair(269, 268));
  edges.push_back(std::make_pair(269, 270));
  edges.push_back(std::make_pair(270, 305));
  edges.push_back(std::make_pair(271, 270));
  edges.push_back(std::make_pair(271, 308));
  edges.push_back(std::make_pair(272, 271));
  edges.push_back(std::make_pair(273, 272));
  edges.push_back(std::make_pair(273, 274));
  edges.push_back(std::make_pair(274, 309));
  edges.push_back(std::make_pair(275, 274));
  edges.push_back(std::make_pair(275, 312));
  edges.push_back(std::make_pair(276, 275));
  edges.push_back(std::make_pair(277, 276));
  edges.push_back(std::make_pair(277, 278));
  edges.push_back(std::make_pair(278, 313));
  edges.push_back(std::make_pair(279, 278));
  edges.push_back(std::make_pair(279, 316));
  edges.push_back(std::make_pair(280, 279));
  edges.push_back(std::make_pair(281, 280));
  edges.push_back(std::make_pair(281, 282));
  edges.push_back(std::make_pair(282, 317));
  edges.push_back(std::make_pair(283, 282));
  edges.push_back(std::make_pair(283, 320));
  edges.push_back(std::make_pair(284, 283));
  edges.push_back(std::make_pair(285, 284));
  edges.push_back(std::make_pair(285, 286));
  edges.push_back(std::make_pair(286, 321));
  edges.push_back(std::make_pair(287, 286));
  edges.push_back(std::make_pair(287, 288));
  edges.push_back(std::make_pair(288, 323));
  edges.push_back(std::make_pair(289, 288));
  edges.push_back(std::make_pair(289, 290));
  edges.push_back(std::make_pair(290, 291));
  edges.push_back(std::make_pair(290, 325));
  edges.push_back(std::make_pair(291, 328));
  edges.push_back(std::make_pair(292, 293));
  edges.push_back(std::make_pair(292, 291));
  edges.push_back(std::make_pair(293, 294));
  edges.push_back(std::make_pair(294, 295));
  edges.push_back(std::make_pair(294, 329));
  edges.push_back(std::make_pair(295, 332));
  edges.push_back(std::make_pair(296, 295));
  edges.push_back(std::make_pair(297, 296));
  edges.push_back(std::make_pair(297, 298));
  edges.push_back(std::make_pair(298, 299));
  edges.push_back(std::make_pair(298, 333));
  edges.push_back(std::make_pair(299, 336));
  edges.push_back(std::make_pair(300, 299));
  edges.push_back(std::make_pair(301, 300));
  edges.push_back(std::make_pair(301, 302));
  edges.push_back(std::make_pair(302, 337));
  edges.push_back(std::make_pair(303, 302));
  edges.push_back(std::make_pair(303, 340));
  edges.push_back(std::make_pair(304, 303));
  edges.push_back(std::make_pair(305, 304));
  edges.push_back(std::make_pair(305, 306));
  edges.push_back(std::make_pair(306, 341));
  edges.push_back(std::make_pair(307, 306));
  edges.push_back(std::make_pair(307, 344));
  edges.push_back(std::make_pair(308, 307));
  edges.push_back(std::make_pair(309, 308));
  edges.push_back(std::make_pair(309, 310));
  edges.push_back(std::make_pair(310, 345));
  edges.push_back(std::make_pair(311, 310));
  edges.push_back(std::make_pair(311, 348));
  edges.push_back(std::make_pair(312, 311));
  edges.push_back(std::make_pair(313, 312));
  edges.push_back(std::make_pair(313, 314));
  edges.push_back(std::make_pair(314, 349));
  edges.push_back(std::make_pair(315, 314));
  edges.push_back(std::make_pair(315, 352));
  edges.push_back(std::make_pair(316, 315));
  edges.push_back(std::make_pair(317, 316));
  edges.push_back(std::make_pair(317, 318));
  edges.push_back(std::make_pair(318, 353));
  edges.push_back(std::make_pair(319, 318));
  edges.push_back(std::make_pair(319, 356));
  edges.push_back(std::make_pair(320, 319));
  edges.push_back(std::make_pair(321, 320));
  edges.push_back(std::make_pair(321, 322));
  edges.push_back(std::make_pair(322, 357));
  edges.push_back(std::make_pair(323, 322));
  edges.push_back(std::make_pair(323, 324));
  edges.push_back(std::make_pair(324, 359));
  edges.push_back(std::make_pair(325, 324));
  edges.push_back(std::make_pair(325, 326));
  edges.push_back(std::make_pair(326, 327));
  edges.push_back(std::make_pair(326, 361));
  edges.push_back(std::make_pair(327, 364));
  edges.push_back(std::make_pair(328, 329));
  edges.push_back(std::make_pair(328, 327));
  edges.push_back(std::make_pair(329, 330));
  edges.push_back(std::make_pair(330, 331));
  edges.push_back(std::make_pair(330, 365));
  edges.push_back(std::make_pair(331, 368));
  edges.push_back(std::make_pair(332, 331));
  edges.push_back(std::make_pair(333, 332));
  edges.push_back(std::make_pair(333, 334));
  edges.push_back(std::make_pair(334, 335));
  edges.push_back(std::make_pair(334, 369));
  edges.push_back(std::make_pair(335, 372));
  edges.push_back(std::make_pair(336, 335));
  edges.push_back(std::make_pair(337, 336));
  edges.push_back(std::make_pair(337, 338));
  edges.push_back(std::make_pair(338, 373));
  edges.push_back(std::make_pair(339, 338));
  edges.push_back(std::make_pair(339, 376));
  edges.push_back(std::make_pair(340, 339));
  edges.push_back(std::make_pair(341, 340));
  edges.push_back(std::make_pair(341, 342));
  edges.push_back(std::make_pair(342, 377));
  edges.push_back(std::make_pair(343, 342));
  edges.push_back(std::make_pair(343, 380));
  edges.push_back(std::make_pair(344, 343));
  edges.push_back(std::make_pair(345, 344));
  edges.push_back(std::make_pair(345, 346));
  edges.push_back(std::make_pair(346, 381));
  edges.push_back(std::make_pair(347, 346));
  edges.push_back(std::make_pair(347, 384));
  edges.push_back(std::make_pair(348, 347));
  edges.push_back(std::make_pair(349, 348));
  edges.push_back(std::make_pair(349, 350));
  edges.push_back(std::make_pair(350, 385));
  edges.push_back(std::make_pair(351, 350));
  edges.push_back(std::make_pair(351, 388));
  edges.push_back(std::make_pair(352, 351));
  edges.push_back(std::make_pair(353, 352));
  edges.push_back(std::make_pair(353, 354));
  edges.push_back(std::make_pair(354, 389));
  edges.push_back(std::make_pair(355, 354));
  edges.push_back(std::make_pair(355, 392));
  edges.push_back(std::make_pair(356, 355));
  edges.push_back(std::make_pair(357, 356));
  edges.push_back(std::make_pair(357, 358));
  edges.push_back(std::make_pair(358, 393));
  edges.push_back(std::make_pair(359, 358));
  edges.push_back(std::make_pair(359, 360));
  edges.push_back(std::make_pair(360, 395));
  edges.push_back(std::make_pair(361, 360));
  edges.push_back(std::make_pair(361, 362));
  edges.push_back(std::make_pair(362, 363));
  edges.push_back(std::make_pair(362, 397));
  edges.push_back(std::make_pair(363, 400));
  edges.push_back(std::make_pair(364, 365));
  edges.push_back(std::make_pair(364, 363));
  edges.push_back(std::make_pair(365, 366));
  edges.push_back(std::make_pair(366, 367));
  edges.push_back(std::make_pair(366, 401));
  edges.push_back(std::make_pair(367, 404));
  edges.push_back(std::make_pair(368, 367));
  edges.push_back(std::make_pair(369, 368));
  edges.push_back(std::make_pair(369, 370));
  edges.push_back(std::make_pair(370, 371));
  edges.push_back(std::make_pair(370, 405));
  edges.push_back(std::make_pair(371, 408));
  edges.push_back(std::make_pair(372, 371));
  edges.push_back(std::make_pair(373, 372));
  edges.push_back(std::make_pair(373, 374));
  edges.push_back(std::make_pair(374, 409));
  edges.push_back(std::make_pair(375, 374));
  edges.push_back(std::make_pair(375, 412));
  edges.push_back(std::make_pair(376, 375));
  edges.push_back(std::make_pair(377, 376));
  edges.push_back(std::make_pair(377, 378));
  edges.push_back(std::make_pair(378, 413));
  edges.push_back(std::make_pair(379, 378));
  edges.push_back(std::make_pair(379, 416));
  edges.push_back(std::make_pair(380, 379));
  edges.push_back(std::make_pair(381, 380));
  edges.push_back(std::make_pair(381, 382));
  edges.push_back(std::make_pair(382, 417));
  edges.push_back(std::make_pair(383, 382));
  edges.push_back(std::make_pair(383, 420));
  edges.push_back(std::make_pair(384, 383));
  edges.push_back(std::make_pair(385, 384));
  edges.push_back(std::make_pair(385, 386));
  edges.push_back(std::make_pair(386, 421));
  edges.push_back(std::make_pair(387, 386));
  edges.push_back(std::make_pair(387, 424));
  edges.push_back(std::make_pair(388, 387));
  edges.push_back(std::make_pair(389, 388));
  edges.push_back(std::make_pair(389, 390));
  edges.push_back(std::make_pair(390, 425));
  edges.push_back(std::make_pair(391, 390));
  edges.push_back(std::make_pair(391, 428));
  edges.push_back(std::make_pair(392, 391));
  edges.push_back(std::make_pair(393, 392));
  edges.push_back(std::make_pair(393, 394));
  edges.push_back(std::make_pair(394, 429));
  edges.push_back(std::make_pair(395, 394));
  edges.push_back(std::make_pair(395, 396));
  edges.push_back(std::make_pair(396, 431));
  edges.push_back(std::make_pair(397, 396));
  edges.push_back(std::make_pair(397, 398));
  edges.push_back(std::make_pair(398, 399));
  edges.push_back(std::make_pair(398, 433));
  edges.push_back(std::make_pair(399, 436));
  edges.push_back(std::make_pair(400, 401));
  edges.push_back(std::make_pair(400, 399));
  edges.push_back(std::make_pair(401, 402));
  edges.push_back(std::make_pair(402, 403));
  edges.push_back(std::make_pair(402, 437));
  edges.push_back(std::make_pair(403, 440));
  edges.push_back(std::make_pair(404, 403));
  edges.push_back(std::make_pair(405, 404));
  edges.push_back(std::make_pair(405, 406));
  edges.push_back(std::make_pair(406, 407));
  edges.push_back(std::make_pair(406, 441));
  edges.push_back(std::make_pair(407, 444));
  edges.push_back(std::make_pair(408, 407));
  edges.push_back(std::make_pair(409, 408));
  edges.push_back(std::make_pair(409, 410));
  edges.push_back(std::make_pair(410, 445));
  edges.push_back(std::make_pair(411, 410));
  edges.push_back(std::make_pair(411, 448));
  edges.push_back(std::make_pair(412, 411));
  edges.push_back(std::make_pair(413, 412));
  edges.push_back(std::make_pair(413, 414));
  edges.push_back(std::make_pair(414, 449));
  edges.push_back(std::make_pair(415, 414));
  edges.push_back(std::make_pair(415, 452));
  edges.push_back(std::make_pair(416, 415));
  edges.push_back(std::make_pair(417, 416));
  edges.push_back(std::make_pair(417, 418));
  edges.push_back(std::make_pair(418, 453));
  edges.push_back(std::make_pair(419, 418));
  edges.push_back(std::make_pair(419, 456));
  edges.push_back(std::make_pair(420, 419));
  edges.push_back(std::make_pair(421, 420));
  edges.push_back(std::make_pair(421, 422));
  edges.push_back(std::make_pair(422, 457));
  edges.push_back(std::make_pair(423, 422));
  edges.push_back(std::make_pair(423, 460));
  edges.push_back(std::make_pair(424, 423));
  edges.push_back(std::make_pair(425, 424));
  edges.push_back(std::make_pair(425, 426));
  edges.push_back(std::make_pair(426, 461));
  edges.push_back(std::make_pair(427, 426));
  edges.push_back(std::make_pair(427, 464));
  edges.push_back(std::make_pair(428, 427));
  edges.push_back(std::make_pair(429, 428));
  edges.push_back(std::make_pair(429, 430));
  edges.push_back(std::make_pair(430, 465));
  edges.push_back(std::make_pair(431, 430));
  edges.push_back(std::make_pair(431, 432));
  edges.push_back(std::make_pair(432, 467));
  edges.push_back(std::make_pair(433, 432));
  edges.push_back(std::make_pair(433, 434));
  edges.push_back(std::make_pair(434, 435));
  edges.push_back(std::make_pair(434, 469));
  edges.push_back(std::make_pair(435, 472));
  edges.push_back(std::make_pair(436, 435));
  edges.push_back(std::make_pair(437, 436));
  edges.push_back(std::make_pair(437, 438));
  edges.push_back(std::make_pair(438, 439));
  edges.push_back(std::make_pair(438, 473));
  edges.push_back(std::make_pair(439, 476));
  edges.push_back(std::make_pair(440, 439));
  edges.push_back(std::make_pair(441, 440));
  edges.push_back(std::make_pair(441, 442));
  edges.push_back(std::make_pair(442, 443));
  edges.push_back(std::make_pair(442, 477));
  edges.push_back(std::make_pair(443, 480));
  edges.push_back(std::make_pair(444, 443));
  edges.push_back(std::make_pair(445, 444));
  edges.push_back(std::make_pair(445, 446));
  edges.push_back(std::make_pair(446, 447));
  edges.push_back(std::make_pair(446, 481));
  edges.push_back(std::make_pair(447, 484));
  edges.push_back(std::make_pair(448, 447));
  edges.push_back(std::make_pair(449, 448));
  edges.push_back(std::make_pair(449, 450));
  edges.push_back(std::make_pair(450, 451));
  edges.push_back(std::make_pair(450, 485));
  edges.push_back(std::make_pair(451, 488));
  edges.push_back(std::make_pair(452, 453));
  edges.push_back(std::make_pair(452, 451));
  edges.push_back(std::make_pair(453, 454));
  edges.push_back(std::make_pair(454, 489));
  edges.push_back(std::make_pair(455, 454));
  edges.push_back(std::make_pair(455, 492));
  edges.push_back(std::make_pair(456, 457));
  edges.push_back(std::make_pair(456, 455));
  edges.push_back(std::make_pair(457, 458));
  edges.push_back(std::make_pair(458, 493));
  edges.push_back(std::make_pair(459, 458));
  edges.push_back(std::make_pair(459, 496));
  edges.push_back(std::make_pair(460, 461));
  edges.push_back(std::make_pair(460, 459));
  edges.push_back(std::make_pair(461, 462));
  edges.push_back(std::make_pair(462, 463));
  edges.push_back(std::make_pair(462, 497));
  edges.push_back(std::make_pair(463, 500));
  edges.push_back(std::make_pair(464, 465));
  edges.push_back(std::make_pair(464, 463));
  edges.push_back(std::make_pair(465, 466));
  edges.push_back(std::make_pair(466, 467));
  edges.push_back(std::make_pair(466, 501));
  edges.push_back(std::make_pair(467, 468));
  edges.push_back(std::make_pair(468, 503));
  edges.push_back(std::make_pair(469, 468));
  edges.push_back(std::make_pair(469, 470));
  edges.push_back(std::make_pair(470, 471));
  edges.push_back(std::make_pair(470, 505));
  edges.push_back(std::make_pair(471, 508));
  edges.push_back(std::make_pair(472, 471));
  edges.push_back(std::make_pair(473, 472));
  edges.push_back(std::make_pair(473, 474));
  edges.push_back(std::make_pair(474, 475));
  edges.push_back(std::make_pair(474, 509));
  edges.push_back(std::make_pair(475, 512));
  edges.push_back(std::make_pair(476, 475));
  edges.push_back(std::make_pair(477, 476));
  edges.push_back(std::make_pair(477, 478));
  edges.push_back(std::make_pair(478, 479));
  edges.push_back(std::make_pair(478, 513));
  edges.push_back(std::make_pair(479, 516));
  edges.push_back(std::make_pair(480, 481));
  edges.push_back(std::make_pair(480, 479));
  edges.push_back(std::make_pair(481, 482));
  edges.push_back(std::make_pair(482, 483));
  edges.push_back(std::make_pair(482, 517));
  edges.push_back(std::make_pair(483, 520));
  edges.push_back(std::make_pair(484, 485));
  edges.push_back(std::make_pair(484, 483));
  edges.push_back(std::make_pair(485, 486));
  edges.push_back(std::make_pair(486, 487));
  edges.push_back(std::make_pair(486, 521));
  edges.push_back(std::make_pair(487, 524));
  edges.push_back(std::make_pair(488, 489));
  edges.push_back(std::make_pair(488, 487));
  edges.push_back(std::make_pair(489, 490));
  edges.push_back(std::make_pair(490, 491));
  edges.push_back(std::make_pair(490, 525));
  edges.push_back(std::make_pair(491, 528));
  edges.push_back(std::make_pair(492, 491));
  edges.push_back(std::make_pair(493, 492));
  edges.push_back(std::make_pair(493, 494));
  edges.push_back(std::make_pair(494, 529));
  edges.push_back(std::make_pair(495, 494));
  edges.push_back(std::make_pair(495, 532));
  edges.push_back(std::make_pair(496, 495));
  edges.push_back(std::make_pair(497, 496));
  edges.push_back(std::make_pair(497, 498));
  edges.push_back(std::make_pair(498, 533));
  edges.push_back(std::make_pair(499, 498));
  edges.push_back(std::make_pair(499, 536));
  edges.push_back(std::make_pair(500, 501));
  edges.push_back(std::make_pair(500, 499));
  edges.push_back(std::make_pair(501, 502));
  edges.push_back(std::make_pair(502, 503));
  edges.push_back(std::make_pair(502, 537));
  edges.push_back(std::make_pair(503, 504));
  edges.push_back(std::make_pair(504, 539));
  edges.push_back(std::make_pair(505, 504));
  edges.push_back(std::make_pair(505, 506));
  edges.push_back(std::make_pair(506, 507));
  edges.push_back(std::make_pair(506, 541));
  edges.push_back(std::make_pair(507, 544));
  edges.push_back(std::make_pair(508, 507));
  edges.push_back(std::make_pair(509, 508));
  edges.push_back(std::make_pair(509, 510));
  edges.push_back(std::make_pair(510, 511));
  edges.push_back(std::make_pair(510, 545));
  edges.push_back(std::make_pair(511, 548));
  edges.push_back(std::make_pair(512, 511));
  edges.push_back(std::make_pair(513, 512));
  edges.push_back(std::make_pair(513, 514));
  edges.push_back(std::make_pair(514, 515));
  edges.push_back(std::make_pair(514, 549));
  edges.push_back(std::make_pair(515, 552));
  edges.push_back(std::make_pair(516, 515));
  edges.push_back(std::make_pair(517, 516));
  edges.push_back(std::make_pair(517, 518));
  edges.push_back(std::make_pair(518, 519));
  edges.push_back(std::make_pair(518, 553));
  edges.push_back(std::make_pair(519, 556));
  edges.push_back(std::make_pair(520, 519));
  edges.push_back(std::make_pair(521, 520));
  edges.push_back(std::make_pair(521, 522));
  edges.push_back(std::make_pair(522, 523));
  edges.push_back(std::make_pair(522, 557));
  edges.push_back(std::make_pair(523, 560));
  edges.push_back(std::make_pair(524, 523));
  edges.push_back(std::make_pair(525, 524));
  edges.push_back(std::make_pair(525, 526));
  edges.push_back(std::make_pair(526, 527));
  edges.push_back(std::make_pair(526, 561));
  edges.push_back(std::make_pair(527, 564));
  edges.push_back(std::make_pair(528, 529));
  edges.push_back(std::make_pair(528, 527));
  edges.push_back(std::make_pair(529, 530));
  edges.push_back(std::make_pair(530, 565));
  edges.push_back(std::make_pair(531, 530));
  edges.push_back(std::make_pair(531, 568));
  edges.push_back(std::make_pair(532, 533));
  edges.push_back(std::make_pair(532, 531));
  edges.push_back(std::make_pair(533, 534));
  edges.push_back(std::make_pair(534, 569));
  edges.push_back(std::make_pair(535, 534));
  edges.push_back(std::make_pair(535, 572));
  edges.push_back(std::make_pair(536, 537));
  edges.push_back(std::make_pair(536, 535));
  edges.push_back(std::make_pair(537, 538));
  edges.push_back(std::make_pair(538, 539));
  edges.push_back(std::make_pair(538, 573));
  edges.push_back(std::make_pair(539, 540));
  edges.push_back(std::make_pair(540, 541));
  edges.push_back(std::make_pair(540, 575));
  edges.push_back(std::make_pair(541, 542));
  edges.push_back(std::make_pair(542, 543));
  edges.push_back(std::make_pair(542, 577));
  edges.push_back(std::make_pair(543, 578));
  edges.push_back(std::make_pair(544, 543));
  edges.push_back(std::make_pair(545, 544));
  edges.push_back(std::make_pair(545, 546));
  edges.push_back(std::make_pair(546, 579));
  edges.push_back(std::make_pair(547, 546));
  edges.push_back(std::make_pair(547, 580));
  edges.push_back(std::make_pair(548, 547));
  edges.push_back(std::make_pair(549, 548));
  edges.push_back(std::make_pair(549, 550));
  edges.push_back(std::make_pair(550, 581));
  edges.push_back(std::make_pair(551, 550));
  edges.push_back(std::make_pair(551, 582));
  edges.push_back(std::make_pair(552, 553));
  edges.push_back(std::make_pair(552, 551));
  edges.push_back(std::make_pair(553, 554));
  edges.push_back(std::make_pair(554, 555));
  edges.push_back(std::make_pair(554, 583));
  edges.push_back(std::make_pair(555, 584));
  edges.push_back(std::make_pair(556, 557));
  edges.push_back(std::make_pair(556, 555));
  edges.push_back(std::make_pair(557, 558));
  edges.push_back(std::make_pair(558, 559));
  edges.push_back(std::make_pair(558, 585));
  edges.push_back(std::make_pair(559, 586));
  edges.push_back(std::make_pair(560, 561));
  edges.push_back(std::make_pair(560, 559));
  edges.push_back(std::make_pair(561, 562));
  edges.push_back(std::make_pair(562, 563));
  edges.push_back(std::make_pair(562, 587));
  edges.push_back(std::make_pair(563, 588));
  edges.push_back(std::make_pair(564, 565));
  edges.push_back(std::make_pair(564, 563));
  edges.push_back(std::make_pair(565, 566));
  edges.push_back(std::make_pair(566, 589));
  edges.push_back(std::make_pair(567, 566));
  edges.push_back(std::make_pair(567, 590));
  edges.push_back(std::make_pair(568, 569));
  edges.push_back(std::make_pair(568, 567));
  edges.push_back(std::make_pair(569, 570));
  edges.push_back(std::make_pair(570, 591));
  edges.push_back(std::make_pair(571, 570));
  edges.push_back(std::make_pair(571, 592));
  edges.push_back(std::make_pair(572, 573));
  edges.push_back(std::make_pair(572, 571));
  edges.push_back(std::make_pair(573, 574));
  edges.push_back(std::make_pair(574, 593));
  edges.push_back(std::make_pair(575, 574));
  edges.push_back(std::make_pair(575, 576));
  edges.push_back(std::make_pair(577, 576));
  edges.push_back(std::make_pair(579, 578));
  edges.push_back(std::make_pair(581, 580));
  edges.push_back(std::make_pair(583, 582));
  edges.push_back(std::make_pair(585, 584));
  edges.push_back(std::make_pair(587, 586));
  edges.push_back(std::make_pair(589, 588));
  edges.push_back(std::make_pair(591, 590));
  edges.push_back(std::make_pair(593, 592));

  for (auto edge : edges)
    ocgl::addEdge(g, ocgl::getVertex(g, edge.first), ocgl::getVertex(g, edge.second));

  return g;
}
