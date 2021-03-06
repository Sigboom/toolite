#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --version         print cmake installer version
  --prefix=dir      directory in which to install
  --include-subdir  include the power-1.0.1-Darwin subdirectory
  --exclude-subdir  exclude the power-1.0.1-Darwin subdirectory
  --skip-license    accept license
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "power Installer Version: 1.0.1, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage 
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version 
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'
LICENSE
=======

This is an installer created using CPack (https://cmake.org). No license provided.


____cpack__here_doc____
    echo
    echo "Do you accept the license? [yN]: "
    read line leftover
    case ${line} in
      y* | Y*)
        cpack_license_accepted=TRUE;;
      *)
        echo "License not accepted. Exiting ..."
        exit 1;;
    esac
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the power will be installed in:"
    echo "  \"${toplevel}/power-1.0.1-Darwin\""
    echo "Do you want to include the subdirectory power-1.0.1-Darwin?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/power-1.0.1-Darwin"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

extractor="pax -r"
command -v pax > /dev/null 2> /dev/null || extractor="tar xf -"

tail $use_new_tail_syntax +152 "$0" | gunzip | (cd "${toplevel}" && ${extractor}) || cpack_echo_exit "Problem unpacking the power-1.0.1-Darwin"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;

� m�*] �\p�u�(��~ 9v�D�t�-m� ��,��x2h�-���F9������A����C1&��q�5S%u;�=�a:[q��eQmKv��ں�ʞ�TM8��q������#HI�d'��v�۟�ow߾ݽ�]��@�3�\�j�W�~�]�J�s�^��[Y酌.��SQED��)���q%菨Jx�|���c>�Y���a�cуJ�:�1��WV!��_Q����WT��Dt]G���G>�g>���- D��k�+3����54�3p�����-�II�wM�!\F=ȧ܆|�H��(/Z
p����Ѳ�)�Z.��_�R����9\b�[Bz�P�Z�=1#��+�!6����ɇ����9e���-���&l�U��@@V�JL�5����U�߳&���B�Hhq5�9C{W�f��3a3Yy�r2rP�e5�-�/��1���C=��O��=[L	"�wgF=���	ˉC]�Ѱ��3�s��ݔ��2���Q-��sr~�M��oU^��6��9�16����1��<mlعC�o0��e�_ܨ޸2�ǬϷ�p�|����?~9d|�M�0��2l�m�"��#��� dai=��.\�W��ih!��/�MX׆d"�!��o
y�
.Ǧ����l�w���{�~����6.-��i_�Ow� �C��O������4ls��\��������� ��N�ט��/��o9�Д��[yJwpybU���c��HE*R��T�"�>P�/����B�ta�gҗJN��L��/A�/���e�I��K��V�R��A�_��F���#��:�6�i��!D�g����*P�����7��D��5̕NB5UX(�-Ԁ܂Yx?�X���B����@�K����}�2I�1N�~�{�ρSJ:LJ��3�Os�[�9%=�s���uL����9�����(��O�0�<�";���|w	�w�z�i�c]
��&���t��w�y��>����/>�hJ�GG��>����c��	}⾓���;�;V�c�X]g����o�u�:���XM��uIp����O8�8�e(��h����_.�a`	=��4! YN31�{M����L�|�2�F��3�S�A�Cf���Gi�p�S���I�`�9}�݆�w0B�+4�q�!�я7ƽt�h�c������[�K�AӰ��_��B<O˧�����7):���d-JIώ� ���	�`�[�_�/} ����� OƗj �{������G������c�SX�8~����6И�z�&<��e�aTGhˈ���m��L&�x�G�mT��w��Z��o�K5�x�Ҍh��vO9�^}��(��Ƨ{��������3 j��_5J��R�ez�$���׳���˲�r����N?ӆ�6��f��_�[�����z�/<�����G�S ��i��\��0����M�A�����>��Gv:%Yw�
A�&�j_s�/�i��x���sPZ��y�1m�?2Ð6��$s<y#+�Mþ;_����B�Jì/`�d���z����m��@�@�t됞Aƛ�!��۰�װz���G�z&�ҽ"��3��ٔvo=��h��7c���FE�R?�QoT���BSx�)}���Τ�����>����5�5�0S����?�r�L�\L�'�p4M���!m�������J���K��w�%����.��L��GR���w^m�]�F��B����<�)8�tR=A��:�?����7�x�)_���6�H���,����=�:E��Om�:��\��E,����?��W�h~n�,G�7	a���B�璬m�6��|I�W��ZO��7�1���Y�ӯdpF���7���_���wC���ٱ�������B�ި��s��cO�'������@c^��A�f};
�*�]��o�,?�GOMa�-���ƀ����L]�|���ϰ����U+_�q}�A��
�ֱ��6�H���58H�6���W���O[���$0���0�xS� K��r��@ENA8-��"3�ӧ����wҭ뿵}�뿡�=��1�^Oɬ�]��c}��}M�X��RA�M���E0u"[���#sY�P�鰬O�e���p~U�t��O'�O�rI_b�Dy���|[�r)n��_�$q<s���0�N���l�M��:'�=�?��{�s�^-�?��?�4�+_��(�6v�t/멳|i��4�8���DO5���� <��=(/dR=����7%'ٳch�����n ����o���(�:,�NI#��C+:��l=�u\��Qc��w�ua�	�ұT�;4u�`ف��GIvei=��hjj��C�����ɱ["'T.��=�3C����5L�B�װ��E`������UO����V��Sw;u}Խ�����I�f������>�>D�/P���m�n;u����n��_�n���ƨ��n��-IХ--Sk�3�OcW��½��;�w�oc��NcȎ�rCx��{=��1tCG1� ���凡'h>}CG0ԍ�w0�����Cn�F/�C�1D��*�y0�M�=R�Q��nA�o��a��n����,xV,��M��۶��	l?�S6���A�w�߲�W��A�7�<H���v�c����7�S �)ۃ����}��	c��
�LS�-Jo](	w�#�#��&{��V�d+�Z�uAxx�QJܫ�j4"���5��T6�Dl�'Q�E#JD#Ʉ��?�ǃb,zP�HF�"�!�f�q��m�7���I�9(�D�=sjP׻���N�\W�5�$���}�#`K/�bϲ�E��˝��(�>c%D����Rb����b"8a1�]B��|�R��?g>_�-�3+�?���8��r�$����9���������6���z˸#��:����r�{�������܏p�{����HE*R��T�"�HE*R��T�?dZvky�jXV'��l�*d�]�&5�<wfL�ހv(�4$���ȝ��rL�'�X��\$sC�+���]��8�=7�I03t�!\��~UK _�[yXV#���H�
�͖�B�vH�lY��J�SI�;y�<��Kj2��4%.'���J$ ���"[� ���vB�фW�]{�=.Y�Z���-�r�͓7�h�|^�=ȩJFI{�gH��`���[�[I$��.6N;XU�h�Vj�	E��Y�d6@$^���F�&d�{UթhP�������aB�7
w����X����T�0j�&u�a��3�w3�By��V�o+`T%*G��{;��D���}�ūJD���v�T�ȤW�3���"���X63��*�=�W�+�!�P^bV�* %��vU�����h$�����G��Å�{a����YFX��fg��k
-z��ˁn�ܮt��&���5,'#JwL��M��\.UA��Rc�3м:�&t)]�"��cуt\m�n�B2ܐ
2�Gl2qv��� ����t+����!ŏvp��bR��~�d,�}�f��u2c�	֒�{����5 �٬~�6�n�q��-��dl-��T�3��)GVf��b�+S"�c�\bLt9]N���4W��t6׉���6Q�G�w�B�
�������q��y��E�ɧ��z�=t�_���?��Ws���'7s,,`x���q|h�９�x���0���/�m//e����p|��	���X\��[��s|ǽ���(�Oq<��$��"zr�_��r���Eg8^��Q��x��9&���q\�q�b���q�㛖p~�9����q��Op�Y���?���8��a�G8��m�}�	�3/q���C\�{�^�O�!8�9p|�c4��yʟpl<W�ɱ�|E��xN�S��"����l��Q�{?�#P?�*�V���BT~̂߶��m�x�?f��,�f�����~Ƃ_���LJ��2�݂7Yp�����gȂ#|���b�}�H�W�І�t��>�E|G���(#\���ܽp��+�pm� �Å���?�l'�O|g���k���0]���Ձ���O@�\�a���;%\�3�58�����L���e�f?%\���59��L0���U��� 0�������N�3�
�|��0m�_`�?Î�V���
��g[~c�O7���~ڽ�9tn�v�����k���s�$Ȧ��l��!M�Q��C�d{X�Վ�}~"^�Ђ�
5!���R45Ѐ��{�N*3���$��`�Ѯ��4�xdh���^��䊔<p�=_ˡ1�*h!Lܙzcky��Y5�f��*fp[j�����/	��udS�Z�Ӆ�3t�T،��w&x#yb-+Yf���C���\��U~5��z��uր�'4�ft�Ɂ�?�ɦUv����	�;��cp�418мG��7k�Y3fZ)�U�+�A�b�/��7��>|�k� _�v\�ʠ_��` YC͢���o�I	�c�g�M�<3f�c�=��T$��+���9���ω9HWbR�W��=�qT�ɫ��V��������QuI��.�J*��Ԩ���{��\��F4�ZT���b�d%ްx�D��95�]��>�m1Tsb	K�A�h��Zps�0�ߵ��]��&B��LͿN��P�	����jˌ|�����6�Q�ܮldv�n���X�Q�h����a���
�����7��fZk
$^�#�m%�w�h̝�pT�[i��퀎��|�'}6c�Y!�K�}۶��V��bj��T�N���$E�c"��_Xmo�k�������k[��媪������*����ު�����>Zs�?�[v�{��%����U�uWC�����fc)z=Fζ2Y^����zi�زk�	o��o�!u��*0_^��ɠJ㱾�i������U����+k [Ͷ��=Czs��w"K7�/7��9!/ �o�r��dD!�ٿC�+�?��ӓ�����ϛA\6&KƖ�	��Y=YVBrG�ߥ����u�o��_n��[��-��H���Q3*��g�C66���$��+#|���Ĩ4�lF����.l�>p�
��!���w�~��y�ֽ��& K߈��.�����b�#�_7�ߓ1�n4d��n"t;�����7|��7��l�v향ί۶-�o���#c���uB|B�F�dP��� ����V�!(~��� c��H�ڹ>t�WN�X�]n�7��_OU5���SQ\�?�-�t�E�m�+�ͻ,3"�m���i�a�N�i���v��RvB���nL����������f�R����7�}o��*WEq���І���-�Wܮ�q'l:7����-I-�o��U��J�i�a׹�*��&XĄmqů)Aq��������	`��ĳ�ҽ����L�V�o(+F��an��X'���ME�V�"��%��'w� f  