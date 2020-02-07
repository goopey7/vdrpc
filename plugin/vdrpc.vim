let s:rpc_file = '/tmp/vdrpc'

autocmd VimLeave * call system('rm -f ' . s:rpc_file)

command! StartDiscordRpc :call vdrpc#StartDRpc()
command! StopDiscordRpc :call vdrpc#StopDRpc()

if exists("g:vdrpc_autostart")
	if g:vdrpc_autostart == 1
		StartDiscordRpc
	endif
endif
