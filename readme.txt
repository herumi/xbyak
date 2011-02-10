
    C++用x86(IA-32), x64(AMD64, x86-64) JITアセンブラ Xbyak version 2.992

-----------------------------------------------------------------------------
◎概要

これはx86, x64(AMD64, x86-64)のマシン語命令を生成するC++のクラスライブラリです．
プログラム実行時に動的にアセンブルすることが可能です．

-----------------------------------------------------------------------------
◎特徴

・ヘッダファイルオンリー
    xbyak.hをインクルードするだけですぐ利用することができます．
    C++の枠組み内で閉じているため，外部アセンブラは不要です．
    32bit/64bit両対応です．
    対応ニーモニック:特権命令除くx86, MMX/MMX2/SSE/SSE2/SSE3/SSSE3/SSE4/FPU(一部)/AVX

・Windows Xp(32bit, 64bit), Vista/Linux(32bit, 64bit)/Intel Mac対応
    Windows Xp上ではVC2005 Express Ed., VC2008, VC2010,
    Windows Vista
    Linux (kernel 2.4.32)上ではgcc 4.5.0, CentOS 5.1上ではgcc 4.1.2
    Intel Mac
    などで動作確認をしています．

※ gccではand, or, xorなどを演算子として解釈してしまうため，
-fno-operator-namesオプションを追加してコンパイルしてください．

-----------------------------------------------------------------------------
◎準備
xbyak.h
xbyak_bin2hex.h
xbyak_mnemonic.h
これらを同一のパスに入れてインクルードパスに追加してください．

Linuxではmake installで/usr/local/include/xbyakにコピーされます．
-----------------------------------------------------------------------------
◎文法

Xbyak::CodeGenerator クラスを継承し，そのクラスメソッド内でx86, x64アセンブラを
記述します．そのメソッドを呼び出した後，getCode()メソッドを呼び出し，その戻
り値を自分が使いたい関数ポインタに変換して利用します．アセンブルエラーは例外
により通知されます(cf. main.cpp)．

・基本的にnasmの命令で括弧をつければよいです．

mov eax, ebx  --> mov(eax, ebx);
inc ecx           inc(ecx);
ret           --> ret();

・アドレッシング

(ptr|dword|word|byte) [base + index * (1|2|4|8) + displacement]
                      [rip + 32bit disp] ; x64 only
という形で指定します．サイズを指定する必要がない限りptrを使えばよいです．
セレクタはサポートしていません．

mov eax, [ebx+ecx] --> mov (eax, ptr[ebx+ecx]);
test byte [esp], 4 --> test (byte [esp], 4);

(注意) dword, word, byteはクラス変数です．従ってたとえばunsigned intの
つもりでdwordをtypedefしないでください．

・AVX

大抵の3オペランド形式の命令はデスティネーションを省略した形で呼び出すことができます.
FMAについては簡略表記を導入するか検討中です(アイデア募集中).

vaddps(xmm1, xmm2, xmm3); // xmm1 <- xmm2 + xmm3
vaddps(xmm2, xmm3); // xmm2 <- xmm2 + xmm3

vfmadd231pd(xmm1, xmm2, xmm3); // xmm1 <- (xmm2 * xmm3) + xmm1

・ラベル

L(文字列);
で定義します．ジャンプするときはその文字列を指定します．後方参照も可能ですが，
相対アドレスが8ビットに収まらない場合はT_NEARをつけないと実行時に例外が発生
します．

・hasUndefinedLabel()を呼び出して真ならジャンプ先が存在しないことを示します．
コードを見直してください．

L("L1");
    jmp ("L1");

    jmp ("L2");
    ...
    少しの命令の場合．
    ...
L("L2");

    jmp ("L3", T_NEAR);
    ...
    沢山の命令がある場合
    ...
L("L3");

<応用編>

1. MASMライクな@@, @f, @bをサポート

  L("@@"); // <A>
  jmp("@b"); // jmp to <A>
  jmp("@f"); // jmp to <B>
  L("@@"); // <B>
  jmp("@b"); // jmp to <B>

2. ラベルの局所化

ピリオドで始まるラベルをinLocalLabel(), outLocalLabel()で挟むことで局所化できます．

void func1()
{
    inLocalLabel();
    L(".lp"); // <A>
    ...
    jmp(".lp"); // jmpt to <A>
    outLocalLabel();
}

void func2()
{
    L(".lp"); // <B>
    func1();
    jmp(".lp"); // jmp to <B>
}

上記サンプルではinLocalLabel(), outLocalLabel()が無いと，
".lp"ラベルの二重定義エラーになります．

・Xbyak::CodeGenerator()コンストラクタインタフェース

@param maxSize [in] コード生成最大サイズ(デフォルト2048byte)
@param userPtr [in] ユーザ指定メモリ

CodeGenerator(size_t maxSize = DEFAULT_MAX_CODE_SIZE, void *userPtr = 0);

デフォルトコードサイズは2048(=DEFAULT_MAX_CODE_SIZE)バイトです．
それより大きなコードを生成する場合はCodeGenerator()のコンストラクタに指定してください．

class Quantize : public Xbyak::CodeGenerator {
public:
    Quantize()
        : CodeGenerator(8192)
    {
    }
    ...
};

# 動的にしたほうがよいのだが実行属性の管理が面倒でやってません…．

またユーザ指定メモリをコード生成最大サイズと共に指定すると，CodeGeneratorは
指定されたメモリ上にバイト列を生成します．

サポート関数として指定されたアドレスの実行属性を変更するCodeArray::protect()と
与えられたポインタからアライメントされたポインタを取得するCodeArray::getAlignedAddress()
も用意しました．詳細はsample/test0.cppのuse memory allocated by userを参考に
してください．

/**
    change exec permission of memory
    @param addr [in] buffer address
    @param size [in] buffer size
    @param canExec [in] true(enable to exec), false(disable to exec)
    @return true(success), false(failure)
*/
bool CodeArray::protect(const void *addr, size_t size, bool canExec);

/**
    get aligned memory pointer
*/
uint8 *CodeArray::getAlignedAddress(uint8 *addr, size_t alignedSize = ALIGN_SIZE);

その他詳細は各種サンプルを参照してください．
-----------------------------------------------------------------------------
◎マクロ

32bit環境上でコンパイルするとXBYAK32が，64bit環境上でコンパイルするとXBYAK64が
定義されます．さらに64bit環境上ではWindowsならXBYAK64_WIN，gcc上ではXBYAK64_GCC
も定義されます．

-----------------------------------------------------------------------------
◎使用例

test0.cpp ; 簡単な例(x86, x64)
quantize.cpp ; 割り算のJITアセンブルによる量子化の高速化(x86)
calc.cpp ; 与えられた多項式をアセンブルして実行(x86, x64)
           boost(http://www.boost.org/)が必要
bf.cpp ; JIT Brainfuck(x86, x64)

-----------------------------------------------------------------------------
◎注意

MMX/SSE命令はほぼ全て実装されていますが，3D Now!命令や，一部の特殊な
命令は現時点では実装されていません．FPUの80bit浮動小数はサポートしていません．

何かご要望があればご連絡ください．

-----------------------------------------------------------------------------
◎ライセンス

修正された新しいBSDライセンスに従います．
http://www.opensource.jp/licenses/bsd-license.html

sample/{echo,hello}.bfは http://www.kmonos.net/alang/etc/brainfuck.php から
いただきました．

-----------------------------------------------------------------------------
◎履歴

2011/02/10 ver 2.992 beta support one argument syntax for fadd like nasm
2011/02/07 ver 2.991 beta fix pextrw reg, xmm, imm(Thanks to Gabest)
2011/02/04 ver 2.99 beta support AVX
2010/12/08 ver 2.31 fix ptr [rip + 32bit offset], support rtdscp
2010/10/19 ver 2.30 support pclmulqdq, aesdec, aesdeclast, aesenc, aesenclast, aesimc, aeskeygenassist
2010/07/07 ver 2.29 fix call(<label>)
2010/06/17 ver 2.28 move some member functions to public
2010/06/01 ver 2.27 support encoding of mov(reg64, imm) like yasm(not nasm)
2010/05/24 ver 2.26 fix sub(rsp, 1000)
2010/04/26 ver 2.25 add jc/jnc(I forgot to implement them...)
2010/04/16 ver 2.24 change the prototype of rewrite() method
2010/04/15 ver 2.23 fix align() and xbyak_util.h for Mac
2010/02/16 ver 2.22 fix inLocalLabel()/outLocalLabel()
2009/12/09 ver 2.21 support cygwin(gcc 4.3.2)
2009/11/28 ver 2.20 FPUの一部命令サポート
2009/06/25 ver 2.11 64bitモードでの mov(qword[rax], imm); 修正(thanks to Martinさん)
2009/03/10 ver 2.10 jmp/call reg64の冗長なREG.W削除
2009/02/24 ver 2.09 movq reg64, mmx/xmm; movq mmx/xmm, reg64追加
2009/02/13 ver 2.08 movd(xmm7, dword[eax])が0x66を落とすバグ修正(thanks to Gabestさん)
2008/12/30 ver 2.07 call()の相対アドレスが8bit以下のときのバグ修正(thanks to katoさん)
2008/09/18 ver 2.06 @@, @f, @bとラベルの局所化機能追加(thanks to nobu-qさん)
2008/09/18 ver 2.05 ptr [rip + 32bit offset]サポート(thanks to 団子厨(Dango-Chu)さん)
2008/06/03 ver 2.04 align()のポカミス修正．mov(ptr[eax],1);などをエラーに
2008/06/02 ver 2.03 ユーザ定義メモリインタフェースサポート
2008/05/26 ver 2.02 protect()(on Linux)で不正な設定になることがあるのを修正(thanks to sinichiro_hさん)
2008/04/30 ver 2.01 cmpxchg16b, cdqe追加
2008/04/29 ver 2.00 x86/x64-64版公開
2008/04/25 ver 1.90 x64版β公開
2008/04/18 ver 1.12 コード整理
2008/04/14 ver 1.11 コード整理
2008/03/12 ver 1.10 bsf/bsr追加(忘れていた)
2008/02/14 ver 1.09 sub eax, 1234が16bitモードで出力されていたのを修正(thanks to Robertさん)
2007/11/05 ver 1.08 lock, xadd, xchg追加
2007/11/02 ver 1.07 SSSE3/SSE4対応(thanks to 団子厨(Dango-Chu)さん)
2007/09/25 ver 1.06 call((int)関数ポインタ); jmp((int)関数ポインタ);のサポート
2007/08/04 ver 1.05 細かい修正
2007/02/04 後方へのジャンプでT_NEARをつけないときに8bit相対アドレスに入らない
           場合に例外が発生しないバグの修正
2007/01/21 [disp]の形のアドレス生成のバグ修正
           mov (eax|ax|al, [disp]); mov([disp], eax|ax|al);の短い表現選択
2007/01/17 webページ作成
2007/01/04 公開開始

-----------------------------------------------------------------------------
◎著作権者

光成滋生(MITSUNARI Shigeo, herumi at nifty dot com)

---
$Revision: 1.56 $
$Date: 2010/04/16 11:58:22 $
