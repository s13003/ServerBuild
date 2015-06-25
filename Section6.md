# Section 6 AWS(Amazon Web Services)

このセクションではAWS(Amazon Web Services)を使用したサーバー構築を行ないます。

## 講義関連リンク

* [AWS公式サイト](http://aws.amazon.com/jp/)
* [Cloud Design Pattern](http://aws.clouddesignpattern.org/index.php/%E3%83%A1%E3%82%A4%E3%83%B3%E3%83%9A%E3%83%BC%E3%82%B8)

## 6-0 AWSコマンドラインインターフェイスのインストール

#下準備
以下のコマンドを実行
```
sudo -s
export EDITOR=vi
visudo
```
Default env_resetをコメントアウト
開いたファイルに以下を追加
```
Defaults        env_keep="no_proxy NO_PROXY"
Defaults        env_keep+="http_proxy https_proxy ftp_proxy"
Defaults        env_keep+="HTPP_PROXY HTTPS_PROXY FTP_PROXY"
```

適用させるために端末を再起動する

1. 以下のコマンドを実行
```
sudo pip install awscli
```

awsコマンドが使えることを確認する

ブラウザで'https://it-college.signin.aws.amazon.com/console'に接続する

2. アカウントを取得する

## インスタンスの作成
1. AWSのサービス→ EC2→ インスタンス→ インスタンスの作成をクリックする

2. Amazonマシンイメージ(AMI)を'Amazon Linux AMI 2015.03 (HVM), SSD Volume Type - ami-cbf90ecb'で選択

3. 作成をクリック 

4. キーペアをダウンロードする(GUIでいけます！！)
キーペアを公開してはいけないので権限をいじるために以下のコマンドを実行
```
chmod 400 s13003.pem
```


##AWSの設定
端末で以下のコマンドを実行
```
aws configure
```
與那城先生にいただいたアクセスキーを入力し、regionを'ap-northeast-1'にし、formatを'json'にする。

以下のコマンドを実行
```
aws ec2 describe-instances
```
5. ssh接続の確認
```
ssh -i s13003.pem ec2-user@52.69.79.49
```
## 6-1	AWS EC2 + Ansible

1. hostsファイルの作成(以下を参照)  

2. インスタンスを作成する

3. インベントリファイルを作成する(IPは作ったインスタンスのパブリックIP)
[hosts](Section6/hosts)   
2. playbookを作成(以下を参照)   
[playbook](Section6/playbook.yml)   
3. playbookを実行
```
ansible-playbook -i [インベントリファイル] -u ec2 playbook.yml --private-key [pemファイル]   
```
4. ブラウザで自分のパブリックIPに接続   

5. いつもどおりにwordpressをインストール

### AMI(Amazon Machine Image)を作る

1. EC2→ インスタンス→ 自分のインスタンスを右クリック→ イメージの作成→ 名前と、説明を書いて作成   

2. IMGが無事作成されていればおｋ！！   

3. インスタンスの作成→ マイAMI→ 自分のAMIを選択→ そのまま作成

4. 作成したインスタンスにssh接続し、mysqlを動かす
```
sudo service mysqld start
```

5. ブラウザでパブリックIPに接続(さっきとは違うIPなので注意)

6. wordpressに接続できれば完了！
## 6-2 AWS EC2(AMIMOTO)

1. インスタンス作成→ 左に[AWS marketplace]とあるのでクリック   

2. 製品の検索欄に[amimoto]と入力して検索   

3. WordPress powered by AMIMOTO (HHVM)を選択   

4. tc2.microを選択して作成   

5. ssh接続できるか確認する   

6. ブラウザでパブリックIPに接続する   

7. インスタンスIDをいれる

8. インストールしたら終了！

## 6-3 Route53

AWSサービス ＞ Route53 ＞ Create Hosted Zoneをクリック ＞ Dmain nameとcommentを入力してcreateクリック ＞ Import Zone Fileをクリック ＞ Section5で作ったzoneファイルをまるまるコピーしてimportでおｋ！ > Create Record Setをクリック ＞ valueの欄に適当にIPを入力 ＞ 変更されてればおｋ！！

## 6-4 S3

1. 適当にhtmlファイルを作る

2. バケットを作成する

3. コマンドでファイルをアップロード
以下のコマンドを実行
```
aws s3 cp ファイル名 s3://[バケット名]
```

4. アップロードされてればおｋ！！

## 6-5 CloudFront

1. 作ったAMIのパブリックIPにブラウザで接続し、Wordpressがインストールできるか確認する

2. CloudFrontを開いてCreate Distributionをクリック

3. Origin Dmain Nameの欄にパブリックDNSを入力してCreate Distributionをクリック

4. StatusがDeployになるまで待機

5. GeneralをクリックしてDomain Nameをコピーしてブラウザで接続する

6. URLをコピーしてabコマンドを実行
```
ab [URL]
```

7. EC2のパブリックDNSをコピーしてブラウザで接続する

8. URLをコピーしてabコマンドを実行
```
ab [URL]
```

9. CloudFrontを通したほうが早いことがわかればおｋ！！(今回なぜかEC2のが早かった)

## 6-6 RDS

1. RDSを開く ＞ DBインスタンスの起動をクリック

2. MySQLを選択　＞　なんか聞かれるので[いいえ]を選択(無料版)して、次のステップへ

3. DBインスタンスを[db.t2.micro -- 1 vCPU, 1 GiB RAM]にする

4. マルチAZ配置を[はい]にする

5. ストレージタイプを[マグネティック]に設定

6. 残りはDBインスタンスは誰が作ったかをわかるために学籍番号,残りは適当にうめていき、次のステップへ

7. パブリックアクセス可能を[いいえ]にして、データベース名を入力してDBインスタンスの作成をクリック

8. セキュリティグループを編集 ＞ MYSQLの送信元を[0.0.0.0/0]に変更

9. EC2インスタンスに接続し、ssh接続するコマンドを実行
```
mysql -h [エンドポイント] -P [ポート番号] -u [ユーザー名] -p [DB名]
```

10. 接続確認できたら接続を切る(exit)

11. /usr/share/nginx/wordpress/wp-config.phpを削除する
```
sudo rm /usr/share/nginx/wordpress/wp-config.php
```

12. データベースのホスト名をlocalhostから[End Point]に変更

13. 無事インストールできれば終了！！

## 6-7 ELB

1. AMIでインスタンスを３個ほど作成する

2. EC2 ＞ ロードバランサーをクリック

3. ロードバランサーの作成をする

4. インスタンスの登録をする

5. 作成したインスタンスにブラウザで接続し、WordPressをインストールする

6. 作成したインスタンス分の端末を立ち上げてssh接続し、mysqlに接続する
```
mysql -u root -p
```

7. mysqlで以下のコマンドを順番に実行
```
1. use [データベース名]   

2. UPDATE wp_options SET option_value = "/" WHERE option_id in (1,2);

3. exit
```

8. ロードバランサーのDNS名にブラウザで接続する

9. 端末でssh接続した状態で以下のコマンドを実行
```
sudo tail -f /var/log/nginx/accsess.log
```

10. ロードバランサーのDNSに接続したブラウザでF5連打

11. インスタンス分の端末が動けば処理が分散していることが確認できるので終わり！！

## 6-8 API叩いてみよう

AWSは自分で作ったプログラムからもいろいろ制御できます!
なんでもいいのでがんばってプログラム書いてみてね(おすすめはSES)。
