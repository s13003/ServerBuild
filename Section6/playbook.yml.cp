---
- hosts: all
  vars:
    rootpw: hoge
  sudo: yes
  user: ec2-user
  tasks:
    - name: nginxのリポジトリを追加
      yum: name=http://nginx.org/packages/centos/7/noarch/RPMS/nginx-release-centos-7-0.el7.ngx.noarch.rpm state=installed 
    - name: いろいろインスコ
      yum: name={{item}} state=installed
      with_items: 
        - nginx
        - php-mysql
        - php-mbstring
        - php-fpm
        - mariadb
        - mariadb-server 
        - MySQL-python
    - name: nginxの設定ファイルを置き換え
      copy: src=temp/default.conf dest=/etc/nginx/conf.d/
    - name: phpの設定ファイルを置き換え
      copy: src=temp/www.conf dest=/etc/php-fpm.d/

    - name: enable nginx
      service: name={{item}} state=started enabled=yes
      with_items:
        - nginx
        - mariadb
        - php-fpm

    - name: root password
      mysql_user:
        name: root
        password: 'hoge'
        state: present

    - name: set MySQL login setting
      template: src=temp/my.cnf dest=/root/.my.cnf owner=root mode=0600

    - name: create database
      mysql_db: 
        name: wp_db
        state: present
        login_user: root
        login_password: "{{ rootpw }}"

    - name: user add
      mysql_user:
        name: s13003
        priv: "*.*:ALL"
        password: 'hoge'
        state: present
        login_user: root
        login_password: hoge

    - name: Download wordpress
      get_url: 
        url: http://wordpress.org/latest.tar.gz
        dest: /home/vagrant/latest.tar.gz

    - name: Extract archive
      shell: chdir=/usr/share/nginx/ creates=/usr/share/nginx/wordpress /bin/tar xvf /home/vagrant/latest.tar.gz

    - name: Change ownership of WordPress installation
      file:
        path: /usr/share/nginx/wordpress/
        owner: nginx
        group: nginx
        state: directory
        recurse: yes


