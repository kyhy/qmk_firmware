let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/code/qmk_firmware/keyboards/lets_split
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +46 keymaps/serial/keymap.c
badd +0 ~/code/qmk_firmware/keyboards/lets_split/keymaps/serial/snippets.c
badd +0 ~/code/qmk_firmware/keyboards/lets_split/keymaps/serial/keymap_noah.c
argglobal
silent! argdel *
edit keymaps/serial/keymap.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 181 + 182) / 364)
exe 'vert 2resize ' . ((&columns * 182 + 182) / 364)
argglobal
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 45 - ((0 * winheight(0) + 42) / 85)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
45
normal! 0109|
wincmd w
argglobal
edit ~/code/qmk_firmware/keyboards/lets_split/keymaps/serial/keymap_noah.c
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 93 - ((75 * winheight(0) + 42) / 85)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
93
normal! 0
wincmd w
2wincmd w
exe 'vert 1resize ' . ((&columns * 181 + 182) / 364)
exe 'vert 2resize ' . ((&columns * 182 + 182) / 364)
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
