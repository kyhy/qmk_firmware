let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/code/qmk_firmware
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +42 keyboards/ergodox/keymaps/alexjj/readme.md
badd +26 keyboards/ergodox/keymaps/alexjj/keymap.c
badd +1 tmk_core/common/action_layer.c
badd +1 tmk_core/common/action_code.h
badd +1 ~/code/qmk_firmware/tmk_core/common
badd +89 tmk_core/common/action_layer.h
badd +102 tmk_core/common/action_macro.h
badd +56 keyboards/jd45/keymaps/jeebak/keymap.c
badd +297 quantum/quantum_keycodes.h
badd +1 keyboards/lets_split/keymaps/serial/keymap.c
badd +1 ~/code/qmk_firmware/keyboards/lets_split/keymaps/serial
badd +13 keyboards/lets_split/lets_split.h
argglobal
silent! argdel *
edit keyboards/lets_split/keymaps/serial/keymap.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 118 + 119) / 238)
exe 'vert 2resize ' . ((&columns * 119 + 119) / 238)
argglobal
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 72 - ((3 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
72
normal! 02|
wincmd w
argglobal
edit tmk_core/common/action_layer.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 88 - ((44 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
88
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 118 + 119) / 238)
exe 'vert 2resize ' . ((&columns * 119 + 119) / 238)
tabnext 1
if exists('s:wipebuf') && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
