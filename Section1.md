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
13. 以下のコマンドを実行し、ネットワークの接続が自動で行われるようにする。
  -->"nmcli connection modify enp0s3 connection.autoconnect yes"
     "nmcli connection modify enp0s8 connection.autoconnect yes"
14. "ssh administrator@192.168.56.101"コマンドを実行し、接続を確認。


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
6. 再度"sudo yum"updateを実行する。

## 1-2 Wordpressを動かす(1)

1. "sudo yum install httpd"コマンドを実行。
2. "sudo yum install php php-mbstring"コマンドを実行。
3. "sudo yum install yum install mysql mysql-devel mysql-server mysql-utilities"コマンドを実行。
4. "wget https://ja.wordpress.org/wordpress-4.2.2-ja.zip"コマンドを実行し、日本語版のwordpressを落とす。
5. サーバー再起動時にアパッチとmysqldのサーバーを再起動させるためのコマンド
  --> sudo systemctl enabled mysqld.service
  --> sudo systemctl enabled httpd.service
6. アパッチとsqlを動かす。
  --> sudo service httpd start
  --> sudo service mysql start
7. 正常に動いているか確認
  --> systemctl list-unit-files | grep httpd
  --> systemctl list-unit-files | grep mysqld
8. wordpressを立ち上げれるように設定...以下のコマンドを実行
  --> sudo setenforce 0
  --> sudo sed -i.bak "/SELINUX/s/enforcing/disabled/g" /etc/selinux/config
上記コマンドを実行することでOS起動時にSELinuxが無効になる。
  --> sudo systemctl stop firewalld
  --> sudo systemctl disable firewalld
上記コマンドを実行することでOS起動時にファイアウォールが無効になる。
9. mysqlにログイン
  --> mysql -u root -p
この時点ではパスワードがないため空白のままでおk。
10. mysqlにデータベースの作成とユーザの作成
  --> CREATE DATABASE wordpress_db
上記コマンドをmysqlで実行するとデータベースが作成される。
  --> grant all on データベース名.\* to ユーザ名@localhost identified by パスワード
上記コマンドをmysqlで実行するとユーザが作成される。
11. mysqlで'FLUSH PRIVILEGES'を実行して更新する。
12. wordpressデレクトリを/var/www/html/に移動させる。
13. ブラウザで"http:/[IPアドレス]/wordpress"を開く。
14. インストールすれば終わり！！

<a name="LAMP">※1</a>: Linux・Apache・MySQL・PHPの頭文字を取ってLAMPといいます。
