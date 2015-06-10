$TTL 60
@       IN SOA ns.s13003.com s13003.std.it-college.ac.jp (
        2015060301;
        60;
        900;
        3600;
        60)

        IN      NS    ns.s13003.com.
        IN      MX    10    aspmx.l.google.com.
        IN      NS    ns2.s13003.com.
www     IN      A     172.168.43.67
ns      IN      A     172.168.43.67
ns2     IN      A     172.16.40.71
