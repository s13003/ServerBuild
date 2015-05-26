# Section 2 その他のWebサーバー環境

## 2-1 Vagrantを使用したCentOS7環境の起動
1. 事前に取得したboxファイルを登録
  ---> "vagrant box add CentOS7 取得したファイルのパス --force"

2. Vagrantの初期設定
   作業用ディレクトリの作成
  ---> "mkdir -p ~/ServerBuild/Vagrant_work"
   作成したディレクトリ内で次のコマンドを実行
  ---> "vagrant init"
   'Vagrantfile'が作成されてるのでvimで開き、以下に書き直す
   'confing.vm.box = "base"'  --->  'config.vm.box = "CentOS7"'

   仮想マシンの起動コマンド
   ---> "vagrant up"

   仮想マシンの停止コマンド
   ---> "vagrant halt"

   仮想マシンの一時停止
   ---> "vagrant suspend"

   仮想マシンの破棄
   ---> "bagrant destroy"

   仮想マシンへ接続
   ---> "vagrant ssh"

4. ホストオンリーアダプタの設定
    サーバーを設定したあと、接続するためのIPアドレスを設定し、そのためのNICを追     加するために'config.vm.box = "CentOS7"'の下に以下を追加 
   ---> 'config.vm.network "private_network", ip:"192.168.56.129"'

5. Vagrantfileの反映コマンド 
   ---> "vagrant reload"

1. yumやwgetを使用するときのproxyの設定を行う
   vimで'/etc/profile'を開く
   終わりあたりに以下を追加

   ```
   MY_PROXY_URL="http://172.16.40.1:8888"
   HTTP_PROXY=$MY_PROXY_URL
   HTTPS_PROXY=$MY_PROXY_URL
   FTP_PROXY=$MY_PROXY_URL
   http_proxy=$MY_PROXY_URL
   https_proxy=$MY_PROXY_URL
   ftp_proxy=$MY_PROXY_URL
   export HTTP_PROXY HTTPS_PROXY FTP_PROXY http_proxy https_proxy ftp_proxy
   ```

  追加したら以下のコマンドを実行
  ---> 'source /etc/profile'

  vimで'/etc/yum.conf'を開く
  終わりあたりに以下を追加
  ---> 'proxy=http://172.16.40.1:8888'

  vimで'~/wgetrc'を開く
  終わりあたりに以下を追加

```
  http_proxy = http://172.16.40.1:8888
  https_proxy = http://172.16.40.1:8888
  ftp_proxy = http://172.16.40.1:8888
```

2. wgetのインストール
   ---> "sudo yum install wget"

### Nginxのインストール
3.   Nginxの公式サイトからリポジトリ追加用のrpmをダウンロードするコマンド
   ---> "wget http://nginx.org/packages/centos/7/noarch/RPMS/nginx-release-centos-7-0.e17.ngx.noarch.rpm

4. Nginxをyumでインストール
   ---> "sudo yum install nginx"

5. Nginxを有効にして起動
   ---> "sudo systemctl enable nginx.service"
   ---> "sudo systemctl start nginx.service"

### php-fpmをインストール
6. yumでphp-fpmをインストール
   ---> "sudo yum install php-fpm php-mbstring php-mysql"

7. nginxの設定でphp-fpmが動くように変更する
   ---> "sudo vi /etc/nginx/conf.d/default.conf"

   開いたファイルを以下のように編集 
```
   server {
   listen       80;
   server_name  localhost;

   #charset koi8-r;
   #access_log  /var/log/nginx/log/host.access.log  main;

   location / {
   root   /usr/share/nginx/wordpress;
   index  index.html index.htm index.php;
   }

   #error_page  404              /404.html;

   # redirect server error pages to the static page /50x.html
   #
   error_page   500 502 503 504  /50x.html;
   location = /50x.html {
   root   /usr/share/nginx/html;
   }

   # proxy the PHP scripts to Apache listening on 127.0.0.1:80
   #
   #location ~ \.php$ {
   #    proxy_pass   http://127.0.0.1;
   #}

   # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
   #
   location ~ \.php$ {
   root           /usr/share/nginx/wordpress;
   fastcgi_pass   127.0.0.1:9000;
   fastcgi_index  index.php;
   fastcgi_param  SCRIPT_FILENAME  /usr/share/nginx/wordpress$fastcgi_script_name;
   include        fastcgi_params;
   }

   # deny access to .htaccess files, if Apache's document root
   # concurs with nginx's one
   #
   #location ~ /\.ht {
   #    deny  all;
   #}
   }
 ```

   編集し終わったらwww.confをvimで開く
   ---> sudo vi /etc/php-fpm.d/www.conf

   user = apache   
   group = apache

   となっているので'apache'を'nginx'に変更する
   
8. php-fpmを有効にして起動
   ---> "sudo systemctl enable php-fpm"
   ---> "sudo systemctl start php-fpm"

### MariaDBをインストール
9. yumでmariaDBをインストールする
   ---> "sudo yum install mariadb mariadb-server"
   文字コードの設定
   'mysqld'の終わりあたりに以下を追加
   ---> "character-set-server=utf8"

10. MariaDBを有効にして起動する。
   ---> "sudo systemctl enable mariadb.service"
   ---> "sudo systemctl start mariadb.service"

11. MariaDBの設定を行う
   ---> "mysql_secure_installation"
   対話形式で色々きかれるが流れに任せる

### MariaDBでユーザ、データベース作成

12. データベースにログイン   
   ---> "mysql -u root -p"   
   パスワードはなしでEnter

13. データベースを作成
   ---> "create database wordpress_db"

14. ユーザを作成して権限を編集
   ---> "grant oll on 'データベース名'.\* to ユーザー名@localhost identified by 'パスワード';"

### 外部から接続するための設定

15. ファイアウォール、SELinuxを無効にする
```
   ---> "sudo systemctl disable firewalld"
   ---> "sudo systemctl stop firewalld"
   ---> "sudo setenforce 0"
```

### Wordpressをインストール

14. wgetでWordpressの最新版をダウンロード   
   ---> "wget https://ja.wordpress.org/latest-ja.zip"

15. unzipをインストール   
   ---> "sudo yum install unzip"

16. ダウンロードしたzipファイルを解凍   
   ---> "unzip latest-ja.zip"

17. でてきたディレクトリを公開ディレクトリに移動する   
   ---> "sudo mv wordpress/ /usr/share/nginx"

18. ブラウザから'http://192.168.56.129/'にアクセスし、wp-configファイルの設定をする。必要事項を入力したら送信。後は流れに身を任せてインストール。

19. IDとパスワードを入力後ログインをクリックし、管理画面を開く。

## 2-3 Wordpressを動かす(3)

Apache HTTP Server2.2とPHP5.5の環境を構築してwordpressを動かすぞ！
今回IPアドレスを192.168.56.130を使ってやっていくよ！

1. vagrant、プロキシの設定をする

2. mysqlのインストール
    リポジトリを追加
    ```
        sudo yum -y install http://dev.mysql.com/get/mysql-community-release-e17-5.noarch.rpm

    ```
    リポジトリのインストール
    ```
        rpm -Uvh mysql-community-release-el7-5.noarch.rpm
    ```

    mysqlcommunityserverをインストール
    ```
    sudo yum -y install mysql-community-server
    ```
    mysqlのバージョンを確認する。
    ```
    mysqld --version
    ```

###データベース、ユーザーの作成
    データベースにログインする   
    ```
    mysql -u root -p
    ```
    
    いつもどおりデータベースを作成、権限などの設定をする。   
    
###Apache HTTP Serverのインストール
3. Apache HTTP Server2.2をダウンロード   
```
    wget http://ftp.jaist.ac.jp/pub/apache/httpd/httpd-2.2.29.tar.gz
```

     ダウンロードしたファイルを解凍   
```
    tar xzf httpd-2.2.29.tar.gz
```
    でてきたディレクトリに移動   
```
    cd httpd-2.2.29
```

4. Makefileを作成   
```
    ./configure
```

5. ビルドする！   
```
    make
```

6. インストールする！！   
```
   sudo make install
```

7. 設定ファイルを開き、内容を書き換える   
```
    sudo vi /usr/local/apache2/conf/httpd.conf
```

    以下のように変更   
```
    #ServerName www.example.com:80
    DirectoryIndex index.htmli
```
↓ ↓ ↓ ↓ ↓ 
```
    ServerName localhost:80
    DirectoryIndex index.html index.php
```

    終わりあたりに以下を追加しphpファイルをPHPスクリプトとして動かすための設定をする   
```
<FilesMatch \.php$>
SetHandler application/x-httpd-php
</FilesMatch>
```

8. バージョンを確認(Server Version2.2.29(Unix)と表示されればおk)   
```
    /usr/local/apache2/bin/apachect1 -v
```

9. サーバーを起動する   
```
    sudo /usr/local/apache2/bin/apachect1 -k start
```

10. サーバーを停止する
```
    sudo /usr/local/apache2/bin/apachect1 -k stop
```

### libxml2ソースファイルのダウンロードとインストール

## PHP5.5インストール時に必要なlibxml2をインストールする

1. libxml2インストールに必要なPythonのパッケージをインストール   
```
    sudo yum -y install python-devel
```

2. libxml2ソールファイルをダウンロード
```
wget http://xmlsoft.org/sources/libxml2-2.9.2.tar.gz
```

3. ダウンロードしたファイルを解凍して移動
```
tar xzf libxml2-2.9.2.tar.gz
cd libxml2-2.9.2
```

4. Makefileを作成し、ビルドとインストールをします。
```
./configure
make
sudo make install
```

### PHP5.5のインストール
1. PHPのソースファイルをダウンロードする
```
    wget http://jp2.php.net/get/php-5.5.25.tar.gz/from/this/mirror
```
   ダウンロードしたファイルを解凍
```
    tar xzf mirror
```
   解凍後ディレクトリを移動
```
   cd php-5.5.25
```
   ./configure
   --with-apxs2=/usr/local/apache2/bin/apxs \
   --with-mysql \
```

   1. ビルドしてインストール
```
    make 
    sudo make install
```
   2. バージョンを確認
```
   php -v
```
   
### Wordpressのインストール

1. Wordpress最新版をダウンロード
```
   wget http://ja.wordpress.org/latest-ja.zip
```

2. unzipをインストールする
```
   sudo yum install unzip
```

3. ダウンロードしたファイルを解凍する
```
   unzip latest-ja.zip
```

4. 解凍したディレクトリを公開ディレクトリに移動させる
```
   sudo mv wordpress/ /usr/local/apache2/htdocs/
```

5. http://192.168.56.130/wordpressにブラウザしてwordpressが開くのを確認する

6. 流れに身をまかせて色々入力

7. wp-config.phpファイルを手動で作成し、表示されたテキストをコピー＆ペーストする

8. 2-3終了！！

### 2-4 ベンチマークを取る

# abコマンドのインストール
1. Ubuntu側にabコマンドをインストールする
```
   sudo apt-get install apache2-utils
```

2. ベンチマーク実行
 　※ 同時接続数100、リクエスト数100
```
   ab -n 1000 -c 100 http://192.168.56.131:80/
```

### PageSpeed
# Google ChromeにPageSpeed拡張をインストールし、ベンチマークを取る。

1. chromeウェブストアにアクセスしPageSpeedをインストールする。

2. http://192.168.56.130/wordpress/にアクセスする。

3. [Ctrl+Shift+i]を押してPageSpeedタブをクリックする。

4. [START ANALYZING]をクリックしてベンチマークを実行する

# Wordpressの高速化  

立ち上げたWordPressを高速化し、abとPageSpeedを使用して、改善されたか確認。

1. apacheでコンテンツを圧縮するのに必要なモジュールをコンパイルする。

# WP-SUPER-CACHEのインストール
```
wget https://downloads.wordpress.org/plugin/wp-super-cache.1.4.4.zip 
```
2. 落としたzipファイルを解凍する
```
unzip wp-super-cache.1.4.4.zip
```

3. でてきたファイルを移動させる。   
```
sudo mv wp-super-cache /usr/local/apache2/htdocs/wordpress/wp-content/plugins/
```

4. wordpressでプラグインを有効化させる。

5.もう一度ベンチマークを実行し、スコアをはかる。

6. 点数が上がってれば終了！

## 2-5 セキュリティチェック

サーバーを構築したとしても、セキュリティがガバガバではいろんな意味で駄目です。
Webアプリケーションの脆弱性を突かれたり、設定したサーバーに脆弱性があったりした場合、
情報漏洩とか乗っ取りとか踏み台とかされるとアレです。

定期的にセキュリティチェックを行なう必要があります。

(やり方は後で)

セキュリティチェックを行ない、不具合があるようでしたら修正を行なって再度セキュリティチェックを行ないます。
(可能な限り不具合がなくなるまでチェック&fixを行ないます。)
