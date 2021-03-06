# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef RTIBOOST_PREPROCESSOR_SEQ_ENUM_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_ENUM_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/seq/size.hpp>
#
# /* RTIBOOST_PP_SEQ_ENUM */
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_ENUM(seq) RTIBOOST_PP_SEQ_ENUM_I(seq)
#    define RTIBOOST_PP_SEQ_ENUM_I(seq) RTIBOOST_PP_CAT(RTIBOOST_PP_SEQ_ENUM_, RTIBOOST_PP_SEQ_SIZE(seq)) seq
# elif RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_SEQ_ENUM(seq) RTIBOOST_PP_SEQ_ENUM_I(RTIBOOST_PP_SEQ_SIZE(seq), seq)
#    define RTIBOOST_PP_SEQ_ENUM_I(size, seq) RTIBOOST_PP_CAT(RTIBOOST_PP_SEQ_ENUM_, size) seq
# else
#    define RTIBOOST_PP_SEQ_ENUM(seq) RTIBOOST_PP_CAT(RTIBOOST_PP_SEQ_ENUM_, RTIBOOST_PP_SEQ_SIZE(seq)) seq
# endif
#
# define RTIBOOST_PP_SEQ_ENUM_1(x) x
# define RTIBOOST_PP_SEQ_ENUM_2(x) x, RTIBOOST_PP_SEQ_ENUM_1
# define RTIBOOST_PP_SEQ_ENUM_3(x) x, RTIBOOST_PP_SEQ_ENUM_2
# define RTIBOOST_PP_SEQ_ENUM_4(x) x, RTIBOOST_PP_SEQ_ENUM_3
# define RTIBOOST_PP_SEQ_ENUM_5(x) x, RTIBOOST_PP_SEQ_ENUM_4
# define RTIBOOST_PP_SEQ_ENUM_6(x) x, RTIBOOST_PP_SEQ_ENUM_5
# define RTIBOOST_PP_SEQ_ENUM_7(x) x, RTIBOOST_PP_SEQ_ENUM_6
# define RTIBOOST_PP_SEQ_ENUM_8(x) x, RTIBOOST_PP_SEQ_ENUM_7
# define RTIBOOST_PP_SEQ_ENUM_9(x) x, RTIBOOST_PP_SEQ_ENUM_8
# define RTIBOOST_PP_SEQ_ENUM_10(x) x, RTIBOOST_PP_SEQ_ENUM_9
# define RTIBOOST_PP_SEQ_ENUM_11(x) x, RTIBOOST_PP_SEQ_ENUM_10
# define RTIBOOST_PP_SEQ_ENUM_12(x) x, RTIBOOST_PP_SEQ_ENUM_11
# define RTIBOOST_PP_SEQ_ENUM_13(x) x, RTIBOOST_PP_SEQ_ENUM_12
# define RTIBOOST_PP_SEQ_ENUM_14(x) x, RTIBOOST_PP_SEQ_ENUM_13
# define RTIBOOST_PP_SEQ_ENUM_15(x) x, RTIBOOST_PP_SEQ_ENUM_14
# define RTIBOOST_PP_SEQ_ENUM_16(x) x, RTIBOOST_PP_SEQ_ENUM_15
# define RTIBOOST_PP_SEQ_ENUM_17(x) x, RTIBOOST_PP_SEQ_ENUM_16
# define RTIBOOST_PP_SEQ_ENUM_18(x) x, RTIBOOST_PP_SEQ_ENUM_17
# define RTIBOOST_PP_SEQ_ENUM_19(x) x, RTIBOOST_PP_SEQ_ENUM_18
# define RTIBOOST_PP_SEQ_ENUM_20(x) x, RTIBOOST_PP_SEQ_ENUM_19
# define RTIBOOST_PP_SEQ_ENUM_21(x) x, RTIBOOST_PP_SEQ_ENUM_20
# define RTIBOOST_PP_SEQ_ENUM_22(x) x, RTIBOOST_PP_SEQ_ENUM_21
# define RTIBOOST_PP_SEQ_ENUM_23(x) x, RTIBOOST_PP_SEQ_ENUM_22
# define RTIBOOST_PP_SEQ_ENUM_24(x) x, RTIBOOST_PP_SEQ_ENUM_23
# define RTIBOOST_PP_SEQ_ENUM_25(x) x, RTIBOOST_PP_SEQ_ENUM_24
# define RTIBOOST_PP_SEQ_ENUM_26(x) x, RTIBOOST_PP_SEQ_ENUM_25
# define RTIBOOST_PP_SEQ_ENUM_27(x) x, RTIBOOST_PP_SEQ_ENUM_26
# define RTIBOOST_PP_SEQ_ENUM_28(x) x, RTIBOOST_PP_SEQ_ENUM_27
# define RTIBOOST_PP_SEQ_ENUM_29(x) x, RTIBOOST_PP_SEQ_ENUM_28
# define RTIBOOST_PP_SEQ_ENUM_30(x) x, RTIBOOST_PP_SEQ_ENUM_29
# define RTIBOOST_PP_SEQ_ENUM_31(x) x, RTIBOOST_PP_SEQ_ENUM_30
# define RTIBOOST_PP_SEQ_ENUM_32(x) x, RTIBOOST_PP_SEQ_ENUM_31
# define RTIBOOST_PP_SEQ_ENUM_33(x) x, RTIBOOST_PP_SEQ_ENUM_32
# define RTIBOOST_PP_SEQ_ENUM_34(x) x, RTIBOOST_PP_SEQ_ENUM_33
# define RTIBOOST_PP_SEQ_ENUM_35(x) x, RTIBOOST_PP_SEQ_ENUM_34
# define RTIBOOST_PP_SEQ_ENUM_36(x) x, RTIBOOST_PP_SEQ_ENUM_35
# define RTIBOOST_PP_SEQ_ENUM_37(x) x, RTIBOOST_PP_SEQ_ENUM_36
# define RTIBOOST_PP_SEQ_ENUM_38(x) x, RTIBOOST_PP_SEQ_ENUM_37
# define RTIBOOST_PP_SEQ_ENUM_39(x) x, RTIBOOST_PP_SEQ_ENUM_38
# define RTIBOOST_PP_SEQ_ENUM_40(x) x, RTIBOOST_PP_SEQ_ENUM_39
# define RTIBOOST_PP_SEQ_ENUM_41(x) x, RTIBOOST_PP_SEQ_ENUM_40
# define RTIBOOST_PP_SEQ_ENUM_42(x) x, RTIBOOST_PP_SEQ_ENUM_41
# define RTIBOOST_PP_SEQ_ENUM_43(x) x, RTIBOOST_PP_SEQ_ENUM_42
# define RTIBOOST_PP_SEQ_ENUM_44(x) x, RTIBOOST_PP_SEQ_ENUM_43
# define RTIBOOST_PP_SEQ_ENUM_45(x) x, RTIBOOST_PP_SEQ_ENUM_44
# define RTIBOOST_PP_SEQ_ENUM_46(x) x, RTIBOOST_PP_SEQ_ENUM_45
# define RTIBOOST_PP_SEQ_ENUM_47(x) x, RTIBOOST_PP_SEQ_ENUM_46
# define RTIBOOST_PP_SEQ_ENUM_48(x) x, RTIBOOST_PP_SEQ_ENUM_47
# define RTIBOOST_PP_SEQ_ENUM_49(x) x, RTIBOOST_PP_SEQ_ENUM_48
# define RTIBOOST_PP_SEQ_ENUM_50(x) x, RTIBOOST_PP_SEQ_ENUM_49
# define RTIBOOST_PP_SEQ_ENUM_51(x) x, RTIBOOST_PP_SEQ_ENUM_50
# define RTIBOOST_PP_SEQ_ENUM_52(x) x, RTIBOOST_PP_SEQ_ENUM_51
# define RTIBOOST_PP_SEQ_ENUM_53(x) x, RTIBOOST_PP_SEQ_ENUM_52
# define RTIBOOST_PP_SEQ_ENUM_54(x) x, RTIBOOST_PP_SEQ_ENUM_53
# define RTIBOOST_PP_SEQ_ENUM_55(x) x, RTIBOOST_PP_SEQ_ENUM_54
# define RTIBOOST_PP_SEQ_ENUM_56(x) x, RTIBOOST_PP_SEQ_ENUM_55
# define RTIBOOST_PP_SEQ_ENUM_57(x) x, RTIBOOST_PP_SEQ_ENUM_56
# define RTIBOOST_PP_SEQ_ENUM_58(x) x, RTIBOOST_PP_SEQ_ENUM_57
# define RTIBOOST_PP_SEQ_ENUM_59(x) x, RTIBOOST_PP_SEQ_ENUM_58
# define RTIBOOST_PP_SEQ_ENUM_60(x) x, RTIBOOST_PP_SEQ_ENUM_59
# define RTIBOOST_PP_SEQ_ENUM_61(x) x, RTIBOOST_PP_SEQ_ENUM_60
# define RTIBOOST_PP_SEQ_ENUM_62(x) x, RTIBOOST_PP_SEQ_ENUM_61
# define RTIBOOST_PP_SEQ_ENUM_63(x) x, RTIBOOST_PP_SEQ_ENUM_62
# define RTIBOOST_PP_SEQ_ENUM_64(x) x, RTIBOOST_PP_SEQ_ENUM_63
# define RTIBOOST_PP_SEQ_ENUM_65(x) x, RTIBOOST_PP_SEQ_ENUM_64
# define RTIBOOST_PP_SEQ_ENUM_66(x) x, RTIBOOST_PP_SEQ_ENUM_65
# define RTIBOOST_PP_SEQ_ENUM_67(x) x, RTIBOOST_PP_SEQ_ENUM_66
# define RTIBOOST_PP_SEQ_ENUM_68(x) x, RTIBOOST_PP_SEQ_ENUM_67
# define RTIBOOST_PP_SEQ_ENUM_69(x) x, RTIBOOST_PP_SEQ_ENUM_68
# define RTIBOOST_PP_SEQ_ENUM_70(x) x, RTIBOOST_PP_SEQ_ENUM_69
# define RTIBOOST_PP_SEQ_ENUM_71(x) x, RTIBOOST_PP_SEQ_ENUM_70
# define RTIBOOST_PP_SEQ_ENUM_72(x) x, RTIBOOST_PP_SEQ_ENUM_71
# define RTIBOOST_PP_SEQ_ENUM_73(x) x, RTIBOOST_PP_SEQ_ENUM_72
# define RTIBOOST_PP_SEQ_ENUM_74(x) x, RTIBOOST_PP_SEQ_ENUM_73
# define RTIBOOST_PP_SEQ_ENUM_75(x) x, RTIBOOST_PP_SEQ_ENUM_74
# define RTIBOOST_PP_SEQ_ENUM_76(x) x, RTIBOOST_PP_SEQ_ENUM_75
# define RTIBOOST_PP_SEQ_ENUM_77(x) x, RTIBOOST_PP_SEQ_ENUM_76
# define RTIBOOST_PP_SEQ_ENUM_78(x) x, RTIBOOST_PP_SEQ_ENUM_77
# define RTIBOOST_PP_SEQ_ENUM_79(x) x, RTIBOOST_PP_SEQ_ENUM_78
# define RTIBOOST_PP_SEQ_ENUM_80(x) x, RTIBOOST_PP_SEQ_ENUM_79
# define RTIBOOST_PP_SEQ_ENUM_81(x) x, RTIBOOST_PP_SEQ_ENUM_80
# define RTIBOOST_PP_SEQ_ENUM_82(x) x, RTIBOOST_PP_SEQ_ENUM_81
# define RTIBOOST_PP_SEQ_ENUM_83(x) x, RTIBOOST_PP_SEQ_ENUM_82
# define RTIBOOST_PP_SEQ_ENUM_84(x) x, RTIBOOST_PP_SEQ_ENUM_83
# define RTIBOOST_PP_SEQ_ENUM_85(x) x, RTIBOOST_PP_SEQ_ENUM_84
# define RTIBOOST_PP_SEQ_ENUM_86(x) x, RTIBOOST_PP_SEQ_ENUM_85
# define RTIBOOST_PP_SEQ_ENUM_87(x) x, RTIBOOST_PP_SEQ_ENUM_86
# define RTIBOOST_PP_SEQ_ENUM_88(x) x, RTIBOOST_PP_SEQ_ENUM_87
# define RTIBOOST_PP_SEQ_ENUM_89(x) x, RTIBOOST_PP_SEQ_ENUM_88
# define RTIBOOST_PP_SEQ_ENUM_90(x) x, RTIBOOST_PP_SEQ_ENUM_89
# define RTIBOOST_PP_SEQ_ENUM_91(x) x, RTIBOOST_PP_SEQ_ENUM_90
# define RTIBOOST_PP_SEQ_ENUM_92(x) x, RTIBOOST_PP_SEQ_ENUM_91
# define RTIBOOST_PP_SEQ_ENUM_93(x) x, RTIBOOST_PP_SEQ_ENUM_92
# define RTIBOOST_PP_SEQ_ENUM_94(x) x, RTIBOOST_PP_SEQ_ENUM_93
# define RTIBOOST_PP_SEQ_ENUM_95(x) x, RTIBOOST_PP_SEQ_ENUM_94
# define RTIBOOST_PP_SEQ_ENUM_96(x) x, RTIBOOST_PP_SEQ_ENUM_95
# define RTIBOOST_PP_SEQ_ENUM_97(x) x, RTIBOOST_PP_SEQ_ENUM_96
# define RTIBOOST_PP_SEQ_ENUM_98(x) x, RTIBOOST_PP_SEQ_ENUM_97
# define RTIBOOST_PP_SEQ_ENUM_99(x) x, RTIBOOST_PP_SEQ_ENUM_98
# define RTIBOOST_PP_SEQ_ENUM_100(x) x, RTIBOOST_PP_SEQ_ENUM_99
# define RTIBOOST_PP_SEQ_ENUM_101(x) x, RTIBOOST_PP_SEQ_ENUM_100
# define RTIBOOST_PP_SEQ_ENUM_102(x) x, RTIBOOST_PP_SEQ_ENUM_101
# define RTIBOOST_PP_SEQ_ENUM_103(x) x, RTIBOOST_PP_SEQ_ENUM_102
# define RTIBOOST_PP_SEQ_ENUM_104(x) x, RTIBOOST_PP_SEQ_ENUM_103
# define RTIBOOST_PP_SEQ_ENUM_105(x) x, RTIBOOST_PP_SEQ_ENUM_104
# define RTIBOOST_PP_SEQ_ENUM_106(x) x, RTIBOOST_PP_SEQ_ENUM_105
# define RTIBOOST_PP_SEQ_ENUM_107(x) x, RTIBOOST_PP_SEQ_ENUM_106
# define RTIBOOST_PP_SEQ_ENUM_108(x) x, RTIBOOST_PP_SEQ_ENUM_107
# define RTIBOOST_PP_SEQ_ENUM_109(x) x, RTIBOOST_PP_SEQ_ENUM_108
# define RTIBOOST_PP_SEQ_ENUM_110(x) x, RTIBOOST_PP_SEQ_ENUM_109
# define RTIBOOST_PP_SEQ_ENUM_111(x) x, RTIBOOST_PP_SEQ_ENUM_110
# define RTIBOOST_PP_SEQ_ENUM_112(x) x, RTIBOOST_PP_SEQ_ENUM_111
# define RTIBOOST_PP_SEQ_ENUM_113(x) x, RTIBOOST_PP_SEQ_ENUM_112
# define RTIBOOST_PP_SEQ_ENUM_114(x) x, RTIBOOST_PP_SEQ_ENUM_113
# define RTIBOOST_PP_SEQ_ENUM_115(x) x, RTIBOOST_PP_SEQ_ENUM_114
# define RTIBOOST_PP_SEQ_ENUM_116(x) x, RTIBOOST_PP_SEQ_ENUM_115
# define RTIBOOST_PP_SEQ_ENUM_117(x) x, RTIBOOST_PP_SEQ_ENUM_116
# define RTIBOOST_PP_SEQ_ENUM_118(x) x, RTIBOOST_PP_SEQ_ENUM_117
# define RTIBOOST_PP_SEQ_ENUM_119(x) x, RTIBOOST_PP_SEQ_ENUM_118
# define RTIBOOST_PP_SEQ_ENUM_120(x) x, RTIBOOST_PP_SEQ_ENUM_119
# define RTIBOOST_PP_SEQ_ENUM_121(x) x, RTIBOOST_PP_SEQ_ENUM_120
# define RTIBOOST_PP_SEQ_ENUM_122(x) x, RTIBOOST_PP_SEQ_ENUM_121
# define RTIBOOST_PP_SEQ_ENUM_123(x) x, RTIBOOST_PP_SEQ_ENUM_122
# define RTIBOOST_PP_SEQ_ENUM_124(x) x, RTIBOOST_PP_SEQ_ENUM_123
# define RTIBOOST_PP_SEQ_ENUM_125(x) x, RTIBOOST_PP_SEQ_ENUM_124
# define RTIBOOST_PP_SEQ_ENUM_126(x) x, RTIBOOST_PP_SEQ_ENUM_125
# define RTIBOOST_PP_SEQ_ENUM_127(x) x, RTIBOOST_PP_SEQ_ENUM_126
# define RTIBOOST_PP_SEQ_ENUM_128(x) x, RTIBOOST_PP_SEQ_ENUM_127
# define RTIBOOST_PP_SEQ_ENUM_129(x) x, RTIBOOST_PP_SEQ_ENUM_128
# define RTIBOOST_PP_SEQ_ENUM_130(x) x, RTIBOOST_PP_SEQ_ENUM_129
# define RTIBOOST_PP_SEQ_ENUM_131(x) x, RTIBOOST_PP_SEQ_ENUM_130
# define RTIBOOST_PP_SEQ_ENUM_132(x) x, RTIBOOST_PP_SEQ_ENUM_131
# define RTIBOOST_PP_SEQ_ENUM_133(x) x, RTIBOOST_PP_SEQ_ENUM_132
# define RTIBOOST_PP_SEQ_ENUM_134(x) x, RTIBOOST_PP_SEQ_ENUM_133
# define RTIBOOST_PP_SEQ_ENUM_135(x) x, RTIBOOST_PP_SEQ_ENUM_134
# define RTIBOOST_PP_SEQ_ENUM_136(x) x, RTIBOOST_PP_SEQ_ENUM_135
# define RTIBOOST_PP_SEQ_ENUM_137(x) x, RTIBOOST_PP_SEQ_ENUM_136
# define RTIBOOST_PP_SEQ_ENUM_138(x) x, RTIBOOST_PP_SEQ_ENUM_137
# define RTIBOOST_PP_SEQ_ENUM_139(x) x, RTIBOOST_PP_SEQ_ENUM_138
# define RTIBOOST_PP_SEQ_ENUM_140(x) x, RTIBOOST_PP_SEQ_ENUM_139
# define RTIBOOST_PP_SEQ_ENUM_141(x) x, RTIBOOST_PP_SEQ_ENUM_140
# define RTIBOOST_PP_SEQ_ENUM_142(x) x, RTIBOOST_PP_SEQ_ENUM_141
# define RTIBOOST_PP_SEQ_ENUM_143(x) x, RTIBOOST_PP_SEQ_ENUM_142
# define RTIBOOST_PP_SEQ_ENUM_144(x) x, RTIBOOST_PP_SEQ_ENUM_143
# define RTIBOOST_PP_SEQ_ENUM_145(x) x, RTIBOOST_PP_SEQ_ENUM_144
# define RTIBOOST_PP_SEQ_ENUM_146(x) x, RTIBOOST_PP_SEQ_ENUM_145
# define RTIBOOST_PP_SEQ_ENUM_147(x) x, RTIBOOST_PP_SEQ_ENUM_146
# define RTIBOOST_PP_SEQ_ENUM_148(x) x, RTIBOOST_PP_SEQ_ENUM_147
# define RTIBOOST_PP_SEQ_ENUM_149(x) x, RTIBOOST_PP_SEQ_ENUM_148
# define RTIBOOST_PP_SEQ_ENUM_150(x) x, RTIBOOST_PP_SEQ_ENUM_149
# define RTIBOOST_PP_SEQ_ENUM_151(x) x, RTIBOOST_PP_SEQ_ENUM_150
# define RTIBOOST_PP_SEQ_ENUM_152(x) x, RTIBOOST_PP_SEQ_ENUM_151
# define RTIBOOST_PP_SEQ_ENUM_153(x) x, RTIBOOST_PP_SEQ_ENUM_152
# define RTIBOOST_PP_SEQ_ENUM_154(x) x, RTIBOOST_PP_SEQ_ENUM_153
# define RTIBOOST_PP_SEQ_ENUM_155(x) x, RTIBOOST_PP_SEQ_ENUM_154
# define RTIBOOST_PP_SEQ_ENUM_156(x) x, RTIBOOST_PP_SEQ_ENUM_155
# define RTIBOOST_PP_SEQ_ENUM_157(x) x, RTIBOOST_PP_SEQ_ENUM_156
# define RTIBOOST_PP_SEQ_ENUM_158(x) x, RTIBOOST_PP_SEQ_ENUM_157
# define RTIBOOST_PP_SEQ_ENUM_159(x) x, RTIBOOST_PP_SEQ_ENUM_158
# define RTIBOOST_PP_SEQ_ENUM_160(x) x, RTIBOOST_PP_SEQ_ENUM_159
# define RTIBOOST_PP_SEQ_ENUM_161(x) x, RTIBOOST_PP_SEQ_ENUM_160
# define RTIBOOST_PP_SEQ_ENUM_162(x) x, RTIBOOST_PP_SEQ_ENUM_161
# define RTIBOOST_PP_SEQ_ENUM_163(x) x, RTIBOOST_PP_SEQ_ENUM_162
# define RTIBOOST_PP_SEQ_ENUM_164(x) x, RTIBOOST_PP_SEQ_ENUM_163
# define RTIBOOST_PP_SEQ_ENUM_165(x) x, RTIBOOST_PP_SEQ_ENUM_164
# define RTIBOOST_PP_SEQ_ENUM_166(x) x, RTIBOOST_PP_SEQ_ENUM_165
# define RTIBOOST_PP_SEQ_ENUM_167(x) x, RTIBOOST_PP_SEQ_ENUM_166
# define RTIBOOST_PP_SEQ_ENUM_168(x) x, RTIBOOST_PP_SEQ_ENUM_167
# define RTIBOOST_PP_SEQ_ENUM_169(x) x, RTIBOOST_PP_SEQ_ENUM_168
# define RTIBOOST_PP_SEQ_ENUM_170(x) x, RTIBOOST_PP_SEQ_ENUM_169
# define RTIBOOST_PP_SEQ_ENUM_171(x) x, RTIBOOST_PP_SEQ_ENUM_170
# define RTIBOOST_PP_SEQ_ENUM_172(x) x, RTIBOOST_PP_SEQ_ENUM_171
# define RTIBOOST_PP_SEQ_ENUM_173(x) x, RTIBOOST_PP_SEQ_ENUM_172
# define RTIBOOST_PP_SEQ_ENUM_174(x) x, RTIBOOST_PP_SEQ_ENUM_173
# define RTIBOOST_PP_SEQ_ENUM_175(x) x, RTIBOOST_PP_SEQ_ENUM_174
# define RTIBOOST_PP_SEQ_ENUM_176(x) x, RTIBOOST_PP_SEQ_ENUM_175
# define RTIBOOST_PP_SEQ_ENUM_177(x) x, RTIBOOST_PP_SEQ_ENUM_176
# define RTIBOOST_PP_SEQ_ENUM_178(x) x, RTIBOOST_PP_SEQ_ENUM_177
# define RTIBOOST_PP_SEQ_ENUM_179(x) x, RTIBOOST_PP_SEQ_ENUM_178
# define RTIBOOST_PP_SEQ_ENUM_180(x) x, RTIBOOST_PP_SEQ_ENUM_179
# define RTIBOOST_PP_SEQ_ENUM_181(x) x, RTIBOOST_PP_SEQ_ENUM_180
# define RTIBOOST_PP_SEQ_ENUM_182(x) x, RTIBOOST_PP_SEQ_ENUM_181
# define RTIBOOST_PP_SEQ_ENUM_183(x) x, RTIBOOST_PP_SEQ_ENUM_182
# define RTIBOOST_PP_SEQ_ENUM_184(x) x, RTIBOOST_PP_SEQ_ENUM_183
# define RTIBOOST_PP_SEQ_ENUM_185(x) x, RTIBOOST_PP_SEQ_ENUM_184
# define RTIBOOST_PP_SEQ_ENUM_186(x) x, RTIBOOST_PP_SEQ_ENUM_185
# define RTIBOOST_PP_SEQ_ENUM_187(x) x, RTIBOOST_PP_SEQ_ENUM_186
# define RTIBOOST_PP_SEQ_ENUM_188(x) x, RTIBOOST_PP_SEQ_ENUM_187
# define RTIBOOST_PP_SEQ_ENUM_189(x) x, RTIBOOST_PP_SEQ_ENUM_188
# define RTIBOOST_PP_SEQ_ENUM_190(x) x, RTIBOOST_PP_SEQ_ENUM_189
# define RTIBOOST_PP_SEQ_ENUM_191(x) x, RTIBOOST_PP_SEQ_ENUM_190
# define RTIBOOST_PP_SEQ_ENUM_192(x) x, RTIBOOST_PP_SEQ_ENUM_191
# define RTIBOOST_PP_SEQ_ENUM_193(x) x, RTIBOOST_PP_SEQ_ENUM_192
# define RTIBOOST_PP_SEQ_ENUM_194(x) x, RTIBOOST_PP_SEQ_ENUM_193
# define RTIBOOST_PP_SEQ_ENUM_195(x) x, RTIBOOST_PP_SEQ_ENUM_194
# define RTIBOOST_PP_SEQ_ENUM_196(x) x, RTIBOOST_PP_SEQ_ENUM_195
# define RTIBOOST_PP_SEQ_ENUM_197(x) x, RTIBOOST_PP_SEQ_ENUM_196
# define RTIBOOST_PP_SEQ_ENUM_198(x) x, RTIBOOST_PP_SEQ_ENUM_197
# define RTIBOOST_PP_SEQ_ENUM_199(x) x, RTIBOOST_PP_SEQ_ENUM_198
# define RTIBOOST_PP_SEQ_ENUM_200(x) x, RTIBOOST_PP_SEQ_ENUM_199
# define RTIBOOST_PP_SEQ_ENUM_201(x) x, RTIBOOST_PP_SEQ_ENUM_200
# define RTIBOOST_PP_SEQ_ENUM_202(x) x, RTIBOOST_PP_SEQ_ENUM_201
# define RTIBOOST_PP_SEQ_ENUM_203(x) x, RTIBOOST_PP_SEQ_ENUM_202
# define RTIBOOST_PP_SEQ_ENUM_204(x) x, RTIBOOST_PP_SEQ_ENUM_203
# define RTIBOOST_PP_SEQ_ENUM_205(x) x, RTIBOOST_PP_SEQ_ENUM_204
# define RTIBOOST_PP_SEQ_ENUM_206(x) x, RTIBOOST_PP_SEQ_ENUM_205
# define RTIBOOST_PP_SEQ_ENUM_207(x) x, RTIBOOST_PP_SEQ_ENUM_206
# define RTIBOOST_PP_SEQ_ENUM_208(x) x, RTIBOOST_PP_SEQ_ENUM_207
# define RTIBOOST_PP_SEQ_ENUM_209(x) x, RTIBOOST_PP_SEQ_ENUM_208
# define RTIBOOST_PP_SEQ_ENUM_210(x) x, RTIBOOST_PP_SEQ_ENUM_209
# define RTIBOOST_PP_SEQ_ENUM_211(x) x, RTIBOOST_PP_SEQ_ENUM_210
# define RTIBOOST_PP_SEQ_ENUM_212(x) x, RTIBOOST_PP_SEQ_ENUM_211
# define RTIBOOST_PP_SEQ_ENUM_213(x) x, RTIBOOST_PP_SEQ_ENUM_212
# define RTIBOOST_PP_SEQ_ENUM_214(x) x, RTIBOOST_PP_SEQ_ENUM_213
# define RTIBOOST_PP_SEQ_ENUM_215(x) x, RTIBOOST_PP_SEQ_ENUM_214
# define RTIBOOST_PP_SEQ_ENUM_216(x) x, RTIBOOST_PP_SEQ_ENUM_215
# define RTIBOOST_PP_SEQ_ENUM_217(x) x, RTIBOOST_PP_SEQ_ENUM_216
# define RTIBOOST_PP_SEQ_ENUM_218(x) x, RTIBOOST_PP_SEQ_ENUM_217
# define RTIBOOST_PP_SEQ_ENUM_219(x) x, RTIBOOST_PP_SEQ_ENUM_218
# define RTIBOOST_PP_SEQ_ENUM_220(x) x, RTIBOOST_PP_SEQ_ENUM_219
# define RTIBOOST_PP_SEQ_ENUM_221(x) x, RTIBOOST_PP_SEQ_ENUM_220
# define RTIBOOST_PP_SEQ_ENUM_222(x) x, RTIBOOST_PP_SEQ_ENUM_221
# define RTIBOOST_PP_SEQ_ENUM_223(x) x, RTIBOOST_PP_SEQ_ENUM_222
# define RTIBOOST_PP_SEQ_ENUM_224(x) x, RTIBOOST_PP_SEQ_ENUM_223
# define RTIBOOST_PP_SEQ_ENUM_225(x) x, RTIBOOST_PP_SEQ_ENUM_224
# define RTIBOOST_PP_SEQ_ENUM_226(x) x, RTIBOOST_PP_SEQ_ENUM_225
# define RTIBOOST_PP_SEQ_ENUM_227(x) x, RTIBOOST_PP_SEQ_ENUM_226
# define RTIBOOST_PP_SEQ_ENUM_228(x) x, RTIBOOST_PP_SEQ_ENUM_227
# define RTIBOOST_PP_SEQ_ENUM_229(x) x, RTIBOOST_PP_SEQ_ENUM_228
# define RTIBOOST_PP_SEQ_ENUM_230(x) x, RTIBOOST_PP_SEQ_ENUM_229
# define RTIBOOST_PP_SEQ_ENUM_231(x) x, RTIBOOST_PP_SEQ_ENUM_230
# define RTIBOOST_PP_SEQ_ENUM_232(x) x, RTIBOOST_PP_SEQ_ENUM_231
# define RTIBOOST_PP_SEQ_ENUM_233(x) x, RTIBOOST_PP_SEQ_ENUM_232
# define RTIBOOST_PP_SEQ_ENUM_234(x) x, RTIBOOST_PP_SEQ_ENUM_233
# define RTIBOOST_PP_SEQ_ENUM_235(x) x, RTIBOOST_PP_SEQ_ENUM_234
# define RTIBOOST_PP_SEQ_ENUM_236(x) x, RTIBOOST_PP_SEQ_ENUM_235
# define RTIBOOST_PP_SEQ_ENUM_237(x) x, RTIBOOST_PP_SEQ_ENUM_236
# define RTIBOOST_PP_SEQ_ENUM_238(x) x, RTIBOOST_PP_SEQ_ENUM_237
# define RTIBOOST_PP_SEQ_ENUM_239(x) x, RTIBOOST_PP_SEQ_ENUM_238
# define RTIBOOST_PP_SEQ_ENUM_240(x) x, RTIBOOST_PP_SEQ_ENUM_239
# define RTIBOOST_PP_SEQ_ENUM_241(x) x, RTIBOOST_PP_SEQ_ENUM_240
# define RTIBOOST_PP_SEQ_ENUM_242(x) x, RTIBOOST_PP_SEQ_ENUM_241
# define RTIBOOST_PP_SEQ_ENUM_243(x) x, RTIBOOST_PP_SEQ_ENUM_242
# define RTIBOOST_PP_SEQ_ENUM_244(x) x, RTIBOOST_PP_SEQ_ENUM_243
# define RTIBOOST_PP_SEQ_ENUM_245(x) x, RTIBOOST_PP_SEQ_ENUM_244
# define RTIBOOST_PP_SEQ_ENUM_246(x) x, RTIBOOST_PP_SEQ_ENUM_245
# define RTIBOOST_PP_SEQ_ENUM_247(x) x, RTIBOOST_PP_SEQ_ENUM_246
# define RTIBOOST_PP_SEQ_ENUM_248(x) x, RTIBOOST_PP_SEQ_ENUM_247
# define RTIBOOST_PP_SEQ_ENUM_249(x) x, RTIBOOST_PP_SEQ_ENUM_248
# define RTIBOOST_PP_SEQ_ENUM_250(x) x, RTIBOOST_PP_SEQ_ENUM_249
# define RTIBOOST_PP_SEQ_ENUM_251(x) x, RTIBOOST_PP_SEQ_ENUM_250
# define RTIBOOST_PP_SEQ_ENUM_252(x) x, RTIBOOST_PP_SEQ_ENUM_251
# define RTIBOOST_PP_SEQ_ENUM_253(x) x, RTIBOOST_PP_SEQ_ENUM_252
# define RTIBOOST_PP_SEQ_ENUM_254(x) x, RTIBOOST_PP_SEQ_ENUM_253
# define RTIBOOST_PP_SEQ_ENUM_255(x) x, RTIBOOST_PP_SEQ_ENUM_254
# define RTIBOOST_PP_SEQ_ENUM_256(x) x, RTIBOOST_PP_SEQ_ENUM_255
#
# endif
