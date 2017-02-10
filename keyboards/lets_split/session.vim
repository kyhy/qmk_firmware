let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/code/qmk_firmware/keyboards/lets_split
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +118 keymaps/serial/keymap.c
badd +0 fugitive:///Users/kylee/code/qmk_firmware/.git//b30e6c1c9e1c876ddf95fcc3bc727a04ca6f2abc/keyboards/lets_split/keymaps/serial/keymap.c
argglobal
silent! argdel *
edit keymaps/serial/keymap.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 118 + 119) / 238)
exe '2resize ' . ((&lines * 49 + 31) / 62)
exe 'vert 2resize ' . ((&columns * 119 + 119) / 238)
exe '3resize ' . ((&lines * 10 + 31) / 62)
exe 'vert 3resize ' . ((&columns * 119 + 119) / 238)
argglobal
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 89 - ((10 * winheight(0) + 30) / 60)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
89
normal! 080|
wincmd w
argglobal
edit fugitive:///Users/kylee/code/qmk_firmware/.git//b30e6c1c9e1c876ddf95fcc3bc727a04ca6f2abc/keyboards/lets_split/keymaps/serial/keymap.c
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 118 - ((45 * winheight(0) + 24) / 49)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
118
normal! 066|
wincmd w
argglobal
enew
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=2
setlocal fml=1
setlocal fdn=20
setlocal nofen
wincmd w
exe 'vert 1resize ' . ((&columns * 118 + 119) / 238)
exe '2resize ' . ((&lines * 49 + 31) / 62)
exe 'vert 2resize ' . ((&columns * 119 + 119) / 238)
exe '3resize ' . ((&lines * 10 + 31) / 62)
exe 'vert 3resize ' . ((&columns * 119 + 119) / 238)
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
