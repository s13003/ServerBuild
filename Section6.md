# Section 6 AWS(Amazon Web Services)

このセクションではAWS(Amazon Web Services)を使用したサーバー構築を行ないます。

## 講義関連リンク

* [AWS公式サイト](http://aws.amazon.com/jp/)
* [Cloud Design Pattern](http://aws.clouddesignpattern.org/index.php/%E3%83%A1%E3%82%A4%E3%83%B3%E3%83%9A%E3%83%BC%E3%82%B8)

## 6-0 AWSコマンドラインインターフェイスのインストール

1. 以下のコマンドを実行
```
sudo apt-get install awscli
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
[hosts](Section6/hosts)   
2. ansibleファイルを作成(以下を参照)   
[playbook](Section6/playbook.yml)   
3. ansibleを実行
```
ansible-playbook -i hosts -u [インベントリファイル] playbook.yml --private-key [pemファイル]   
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

6-1では自力(?)で環境構築を行ない、AMIを作成したが、別の人が作ったAMIを使用してサーバーを起動することもできる。

AMIMOTOのWordpressを起動してWordpressが見れることを確認する。

## 6-3 Route53

Route53はAWSが提供するDNSサービス。

5-1で作ったDNSの情報をRoute53に突っ込んでみよう。

## 6-4 S3

S3はSimple Storage Service。その名の通り、ファイルを保存し、(状況によっては)公開するサービス。

てきとーにWebサイトを作り、それをS3にアップロードし、公開してみよう。

S3にアップロードする際にはAWSコマンドラインインターフェイスを使ってね。

## 6-5 CloudFront

CloudFrontはCDNサービスです。CDNって何って?ggrましょう(ちゃんと講義では説明するので聞いてね)。

6-1で作ったAMIを起動し、CloudFrontに登録します。登録して直接アクセスするのとCloudFront経由するのどっちが速いかベンチマークを取ってみましょう。

また、CloudFrondを経由することで、地域ごとにアクセス可能にしたり不可にしたりできるので、それを試してみましょう。

## 6-6 RDS

RDSは…MySQLっぽい奴です。

RDSを立ち上げて、6-1で作ったAMIのWordpressのDBをRDSに向けてみよう。

## 6-7 ELB

ELBはロードバランサーです。すごいよ。

6-1で作ったAMIを3台ぶんくらい立ち上げてELBに登録し、負荷が割り振られているか確認してみよう。

## 6-8 API叩いてみよう

AWSは自分で作ったプログラムからもいろいろ制御できます!
なんでもいいのでがんばってプログラム書いてみてね(おすすめはSES)。
