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

4. 作ったplaybook.ymlをコマンドで実行
```
ansible-playbook -i [インベントリファイル] -u vagrant -k [ymlファイル]
```

5. ブラウザで[自分のIPアドレス]に接続(wordpressはつけないでおっけー)

6. 流れにまかせてインストール

7. Section3-1-1終了！！

## Section3-1-2

1. Vagrantfileからansibleを呼び出す   
   vagrantfileに以下を追加
```
  config.vm.provision "ansible" do |ansible|
  ansible.playbook = "playbook.yml"
end
```

2. 以下のコマンドを実行し、ansibleを呼び出す
```
vagrant provision
```

3. ちゃんと動いたのを確認したら3-2終了!!お疲れ様でした～
