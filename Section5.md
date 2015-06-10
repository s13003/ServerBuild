# Section 5 DNSサーバーを動作させる

## 5-1 bindのインストール
## 5-2 bindの設定
1. 以下を参照
# [playboole.yaml](playbook.yaml)
上記のようにかくとchroot化をやってくれます。


chroot化&自分のゾーンを作ってレコードを返すように設定してください。

[RHEL7のNetworking Guide(英語)](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Networking_Guide/sec-BIND.html)にやり方書かれてるのでそれを参考に設定してください。

また、ゾーン転送を行なって、ミラーリングができていることを確認してください(そのためには2台の仮想マシンが必要になります)
