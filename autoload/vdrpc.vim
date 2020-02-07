let s:rpc_file = '/tmp/vdrpc'

" the directory where the script is located
let s:file_dir = expand('<sfile>:p:h')

func vdrpc#WriteTmp(timer)
	if exists("g:vdrpc_filesize")
		if (g:vdrpc_filesize == 1)
			call writefile(['Editing ' . expand('%:t'), 'Working on ' . expand('%:p:~'), 'Size: ' . expand(getfsize(@%))], s:rpc_file)	
		endif
	else
		call writefile(['Editing ' . expand('%:t'), 'Working on ' . expand('%:p:~')], s:rpc_file)
	endif
endfunc

func vdrpc#StartDRpc()
	call system('bash ' . s:file_dir . '/../vdrpc.sh &')
	let s:timer = timer_start(5000, 'vdrpc#WriteTmp', { 'repeat': -1 })
endfunc

func vdrpc#StopDRpc()
	call system('rm -f ' . s:rpc_file)
	call timer_stop(s:timer)
endfunc
