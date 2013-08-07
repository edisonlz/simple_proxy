simple_proxy
============

Simple Proxy


"""
liuzheng@liuzheng simple_proxy$ telnet 10.103.13.18 30000
Trying 10.103.13.18...
Connected to bjoern.test.api.3g.tudou.com.
Escape character is '^]'.

10.x.x.x:11211 #proxy to memcache
stats #command

STAT pid 26642
STAT uptime 14003042
STAT time 1375876626
STAT version 1.4.15
STAT libevent 2.0.21-stable
STAT pointer_size 64
STAT rusage_user 1237.962801
STAT rusage_system 1953.871966
STAT curr_connections 21
STAT total_connections 59704
STAT connection_structures 138
STAT reserved_fds 20
STAT cmd_get 195331300
STAT cmd_set 100727558
STAT cmd_flush 264
STAT cmd_touch 0
STAT get_hits 108393609
STAT get_misses 86937691
STAT delete_misses 1659
STAT delete_hits 9139693
STAT incr_misses 0
STAT incr_hits 0
STAT decr_misses 0
STAT decr_hits 0
STAT cas_misses 0
STAT cas_hits 0
STAT cas_badval 0
STAT touch_hits 0
STAT touch_misses 0
STAT auth_cmds 0
STAT auth_errors 0
STAT bytes_read 205076756442
STAT bytes_written 296156505061
STAT limit_maxbytes 2147483648
STAT accepting_conns 1
STAT listen_disabled_num 0
STAT threads 4
STAT conn_yields 4703528
STAT hash_power_level 19
STAT hash_bytes 4194304
STAT hash_is_expanding 0
STAT bytes 340733393
STAT curr_items 110863
STAT total_items 99487263
STAT expired_unfetched 51723069
STAT evicted_unfetched 0
STAT evictions 0
STAT reclaimed 61713361
END

"""