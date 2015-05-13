# Section 1 基本のサーバー構築

## 1-1 CentOS 7のインストール

### VirtualBoxへのインストール

1. USBからCentOS 7 Minimal ISO(x86_64)のISOファイルをコピーする。
2. VirtualBox上にインストールする。
3. VirtualBoxで作成する仮想マシンのメモリのサイズは1GBにする。また、ストレージの容量は8GBに設定する。
4. ネットワークアダプター2を設定します。割り当てを「ホストオンリーアダプター」にできなかったので一時的に内部ネットワークに設定。
5. sudo gpasswd -a user_name vboxusersコマンドを実行しvboxusersに自分のアカウントを追加。
6. カーネルのエラーを吐かれた場合、次のコマンドを実行で治るはず！！--> /etc/init.d/vboxdrv setup
7. ネットワークとホスト名→イーサネットEnpOs(3と8)をONにする。
8. ルートパスワードとユーザ設定をする。
9. /etc/sysconfig/network-script/ifcfg-enp0s3と8のONBOOTをyesにする。
10. ネットワークを再起動するコマンドを実行--> "/etc/init.d/network restart"
11. ファイル→ 環境設定からホストオンリーネットワークを追加。
12. ip addrコマンドを入力し、IPアドレスを確認。
13. sshコマンドを実行し、接続を確認。

(ついでなので、公開鍵認証でログインできるようにしておくといいと思いますよ。必須ではないけど。)

### インストール後の設定

1. "yum update"コマンドを実行するとエラーが発生するので/etc/profileをviで開く。
2. 最後あたりに以下を追加。
  MY_PROXY_URL="http://172.16.40.1:8888"

  HTTP_PROXY=$MY_PROXY_URL

  HTTPS_PROXY=$MY_PROXY_URL

  FTP_PROXY=$MY_PROXY_URL

  http_proxy=$MY_PROXY_URL

  https_proxy=$MY_PROXY_URL

  ftp_proxy=$MY_PROXY_URL

  export HTTP_PROXY HTTPS_PROXY FTP_PROXY http_proxy https_proxy ftp_proxy

3. source /etc/profileコマンドを実行。
4. /etc/yum.confをviで開く。
5. 最後あたりに以下を追加。
  proxy=http"//172.16.40.1:8888
6. 

### アップデート

プロキシの設定後、アップデートができるようになっているのでアップデートを行なってください。

## 1-2 Wordpressを動かす(1)

Wordpressを動作させるためには下記のソフトウェアが必要になります。 [※1](#LAMP)

* Apache HTTP Server
* MySQL
* PHP

これらをyumを使用してインストールし、Wordpressをダウンロード、展開して動作させてください。

Wordpressのインストールは[公式サイトに手順が掲載されています](http://wpdocs.sourceforge.jp/WordPress_%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB)のでそちらを参考にすると確実かと思います。

なお、ssh接続できるようになっているので、VirtualBoxの画面からではなく、UbuntuからSSHで接続して設定してください。
(そのほうが圧倒的に楽です。)

Wordpressが表示されたら講師に確認してもらってください。また、今のうちに手順をまとめておいてください。

<a name="LAMP">※1</a>: Linux・Apache・MySQL・PHPの頭文字を取ってLAMPといいます。
