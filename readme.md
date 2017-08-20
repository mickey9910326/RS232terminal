# **RS232terminal**

可在command line執行的輕便terminal。

- - -
## Install
Download the executable file`termainal.exe` and library `pthreadGC2.dll`

- - -
## 安裝
從release頁面中下載執行檔`termainal.exe`及使用函式庫`pthreadGC2.dll`，放到同目錄，並把此目錄加進環境變數 `$PATH`  

- - -
## Usage  
`$terminal [--port <com>] [--baudrate <rate>] [options...] `   

| Options    |  Description    |
| :------------- | :------------- |
| `--port <com>`      | Use desinated port com |
| `-p <com> `         | Same as `--port <com>` |
| `--baudrate <rate>` | Set baudrate |
| `-b <rate>`         | Same as `-b <rate>` |
| `--help`            | Show help messege |
| `-?`                | Same as `--help` |
| `--version`         | Show version |
| `-v`                | Same as `--version` |

- - -
## 中文說明
指令： `$terminal [--port <com>] [--baudrate <rate>] [options...] `  

| Options    |  Description    |
| :------------- | :------------- |
| `--port <com>`      | 使用指定的com來連接 |
| `-p <com> `         | 如同 `--port <com>` |
| `--baudrate <rate>` | 設定鮑率 |
| `-b <rate>`         | 如同 `-b <rate>` |
| `--help`            | 顯示說明文件 |
| `-?`                | 如同  `--help` |
| `--version`         | 顯示版本資訊 |
| `-v`                | 如同  `--version` |

- - -
## example  
`terminal --port 8 -b 38400`

使用鮑率38400，連結到 USB COM 8。

- - -  
## TODO list
