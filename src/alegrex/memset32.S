
# /*
# ---------------------------------------------------------
#   �����͕핗 �` Toho Imitation Style.
#   �v���W�F�N�g�y�[�W http://code.google.com/p/kene-touhou-mohofu/
# ---------------------------------------------------------
# notaz �� http://notaz.gp2x.de/ �� psp picodrive version1.35 source.
# http://notaz.gp2x.de/releases/PicoDrive/PicoDrive_135src.tar.bz2
# �ɓ����Ă������C���������̂ł��B
# -------------------------------------------------------
# */

# /*
# memset32�B�q�֐�
# -------------------------------------------------------
# 32 bit��p�� memset�B
# �Z�b�g����l�̈����� char(8bit) ���� int(32bit)�ɂȂ��Ă���̂ŁA
# �Œ�]���P�ʂ��A4byte�B
# ����� memset(dest, 0x12, 8);
# ���ꂪ memset32(dest, 0x12121212, 2); # 2==8/4
# �ꏏ�B
# -------------------------------------------------------
# ����
# -------------------------------------------------------
# int *dest;    �]����̃A�h���X(C����ł̓|�C���^�Ŏw��)
#               �ʏ�� (void *)�ɃL���X�g���Ďw�肷�鎖�B
# int data;     ���߂����f�[�^�[�B
#               0x12 �Ŗ��߂����Ȃ� 0x12121212 �ƌ��������B
#               0xff �Ŗ��߂����Ȃ� 0xffffffff �ƌ��������B
#               0x12, 0x34, 0x56, 0x78 �� �J��Ԃ��Ŗ��߂����Ȃ� 0x78563412 �ƌ��������B
# int count     �]���ʁBlong(4byte) �P�ʁB
#               count �� 1 ���w�肷��� 4bytes �]������B
# -------------------------------------------------------
# �߂�l
# -------------------------------------------------------
# void          �Ȃ��B
# -------------------------------------------------------
# �d�l�B
# -------------------------------------------------------
# 1. �]���T�C�Y�� 4byte �Ŋ���؂��K�v�����鎖�B
# 2. ������x�]���ʂ������ƁA memset���x���B
# */

.set noreorder
.set noat

.text
.align 4

# /* extern void memset32(s32 *dest, s32 data, int count); */
# /* extern void memset32(int *dest, int data, int count); */
.globl  memset32
.ent    memset32
# /* ------------------------------------------------------ */
# /* [1]. �n�߂� 64bytes .align ����Ă��Ȃ��f�[�^�[��]������B */
# /* 32bytes �łȂ��̂́A�L���b�V������ 64bytes�Ȃ̂ŁB(�v��Ŋm�F: psp�̃L���b�V��������32bytes����Ȃ����������H)  */
memset32:
L_memset32_1st_loop:
    andi    $t0, $a0, 0x3f              # (��ǂݎ��s���đ��v�ȋC������) �]����0 = (dest & 0x3f);  �Ƃɂ��� 64 bytes �� .align �B
    nop                 #

    beqz    $t0, L_memset32_2nd_start   # if (0x00 == �]����0 ) goto L_memset32_2nd_start
    nop                 #
# /* $t0��ǂݎ��s���Ă��ǂ��C�����邪�A�ׂ����d�l������Ȃ������̂Ŏ~�߂Ƃ����B */
# /* a0�̒l�𑽏��M���Ă����ƍœK���o�������ȋC������B(mips�̓A�h���X�I�t�Z�b�g�ɕ������g����B) */

    sw      $a1, 0($a0)                 # *((s32*)dest+0) = (s32)data;  32bit(4bytes) �]��.
    addiu   $a2, -1                     # count--;

    beqz    $a2, L_memset32_return_void            # if (0x00 == count ) { return(); }
    addiu   $a0, 4                      # dest += 4;

    j       L_memset32_1st_loop         # goto L_memset32_1st_loop;
    nop

# /* ------------------------------------------------------ */
# /* [2]. ���� .align����Ă���f�[�^�[��]������B */
                                        # /* srl �� 1�N���b�N�f�B���C ����̂ŁA�y�A�����O�o���܂���B */
L_memset32_2nd_start:
# /* we will do 64 bytes per iteration (cache line). */
    srl     $t0, $a2, 4                 # (srl �͐�ǂݎ��s�o���Ȃ�) �]����1 = (count / 16);
    andi    $a2, $a2, 0x0f              # (�������W�X�^�͐�ǂݎ��s�o���Ȃ�) count &= 0x0f;
    # /* 64byte�����Ȃ�([2].��)�]������K�v�������̂ŁA��([3].)�ցB(64bytes == 16 long words. ) */
    beqz    $t0, L_memset32_quit_check  # if (0x00 == �]����1 ) goto L_memset32_quit_check
    nop                                 #  ������ nop�������������ǂ��B

L_memset32_2nd_loop:
    addiu   $t0, -1                     # �]����1--;
    cache   0x18, ($a0)                 # /* create dirty exclusive. (dest �̃A�h���X���L���b�V�������������ɂ���H)�ǂ��킩��Ȃ�(�v����)�B */
    # /* 16bytes�]��(16==4x4) */
    sw      $a1, 0x00($a0)              # *((s32*)dest+0x00) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x04($a0)              # *((s32*)dest+0x04) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x08($a0)              # *((s32*)dest+0x08) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x0c($a0)              # *((s32*)dest+0x0c) = (s32)data;  32bit(4bytes) �]��.
    # /* 16bytes�]��(16==4x4) */
    sw      $a1, 0x10($a0)              # *((s32*)dest+0x10) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x14($a0)              # *((s32*)dest+0x14) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x18($a0)              # *((s32*)dest+0x18) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x1c($a0)              # *((s32*)dest+0x1c) = (s32)data;  32bit(4bytes) �]��.
    # /* 16bytes�]��(16==4x4) */
    sw      $a1, 0x20($a0)              # *((s32*)dest+0x20) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x24($a0)              # *((s32*)dest+0x24) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x28($a0)              # *((s32*)dest+0x28) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x2c($a0)              # *((s32*)dest+0x2c) = (s32)data;  32bit(4bytes) �]��.
    # /* 16bytes�]��(16==4x4) */
    sw      $a1, 0x30($a0)              # *((s32*)dest+0x30) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x34($a0)              # *((s32*)dest+0x34) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x38($a0)              # *((s32*)dest+0x38) = (s32)data;  32bit(4bytes) �]��.
    sw      $a1, 0x3c($a0)              # *((s32*)dest+0x3c) = (s32)data;  32bit(4bytes) �]��.
    # /* 64bytes�]������(64==4x4x4) */
    # /* �c�肪����Γ]������K�v������̂Ń��[�v */
    bnez    $t0, L_memset32_2nd_loop    # if (0x00 != �]����1 ) goto L_memset32_2nd_loop
    addiu   $a0, 0x40                   # dest += 0x40; // 0x40==64bytes�]�������B

L_memset32_quit_check:
    # /* �c�肪 0 �̏ꍇ�]������K�v�������̂ŏI���B(return ();) */
    beqz    $a2, L_memset32_return_void # if (0x00 == count ) { return(); }
    nop                                 #  ������ nop�������������ǂ��B

# /* ------------------------------------------------------ */
# /* [C]. �Ō�Ɏc��̃f�[�^�[��]������B(C-Loop) */
L_memset32_3rd_loop:
    addiu   $a2, -1                     # count--;
    sw      $a1, 0($a0)                 # *((s32*)dest+0) = (s32)data;  32bit(4bytes) �]��.

    bnez    $a2, L_memset32_3rd_loop
    addiu   $a0, 4                      # dest += 4;

L_memset32_return_void:
    jr      $ra                         # return();
    nop

.set    reorder
.end    memset32