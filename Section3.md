# Section 3 Ansibleによる自動化とテスト

## 3-0 Ansibleのインストール

1. 以下のコマンドを実行し、ansibleをインストールする
```
  sudo apt-get install software-properties-common
  sudo apt-add-repository ppa:ansible/ansible
  sudo apt-get update
  sudo apt-get install ansible
```

### 3-1 ansibleでWordpressを動かす(2)を行なう

## 事前準備

# vagrantのプラグインを入れる
```
sudo vagrant plugin install vagrant-proxyconf   
sudo vagrant plugin install vagrant-vbguest   
```


1. ansibleをUbuntu側で実行した時にyumやwgetしたときにproxyで引っかかるのでVagrantfileを以下の様に編集する
```
Vagrant.configure(2) do |config|            
  if Vagrant.has_plugin?("vagrant-proxyconf")
    config.proxy.http = ENV['http_proxy']
    config.proxy.https = ENV['https_proxy']
    config.proxy.no_proxy = ENV['no_proxy']
  end
```

2. ymlもしくはymal形式のplaybookファイルを自分で作成する   
```
  vi playbook.yml
```

3. playbook.ymlに環境構築自動化するための処理をかく
   以下を参照
# [playbook.yml](playbook.yml)

2-1でWordpressをNginx + PHP + MariaDBでインストールした手順をAnsibleのPlaybookで実行するように記述し、動かしてみてください。
