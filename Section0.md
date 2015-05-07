# Section 0 講義の前のセットアップ

## VirtualBoxのインストール

1. 対応するOSを調べるためのコマンド--->  'dpkg --print-architecture'
2. 公式サイトからVirtialBoxをダウンロード(AMD64)
3. 依存関係の修復コマンドを実行--->  'sudo apt-get -f install'
4. 'sudo apt-get install libsdl1.2debian'コマンドを実行しパッケージをインストール
5. 'sudo dpkg --install virtualbox-4.3_4.3.26-98988~Ubuntu~raring_amd64.deb'コマンドを実行
6. 'virtualbox'コマンドを実行し、動作確認

## 0-2 Vagrantのインストール

1. vargrant公式からファイルをダウンロード(Linux(deb) 64-bit)
2. 'sudo dpkg --install vagrant_1.7.2_x86_64.deb'コマンドを実行
3. 'vagrant -v'を実行し、動作確認
