### Intro

Discord rich presence for [Vim](https://www.vim.org/).

Supported extensions you can see [here](doc/extensions).

### Installation

#### [Vim-Plug](https://github.com/junegunn/vim-plug)

* Add `Plug 'pucka906/vdrpc'` to your vimrc file.
* Reload your vimrc.
* Run `:PlugInstall`

#### [Vundle](https://github.com/VundleVim/Vundle.vim)

* Add `Plugin 'pucka906/vdrpc'` to your vimrc file.
* Reload your vimrc.
* Run `:BundleInstall`

#### [pathogen.vim](https://github.com/tpope/vim-pathogen)

```
git clone https://github.com/pucka906/vdrpc.git ~/.vim/bundle/vdrpc
```

### Build

Compile the main file in the plugin directory with the command:

`gcc -Llib main.c -ldiscord-rpc -o vdrpc-out`

### Usage

To start `:StartDiscordRpc`

To stop `:StopDiscordRpc`

To display the file size in bytes instead of the path to it, put this to your `.vimrc` file:

```vim
let g:vdrpc_filesize = 1
```

To automatically start the plugin, put this in your `.vimrc` file:

```vim
let g:vdrpc_autostart = 1
```
