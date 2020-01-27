cat ip_filter.tsv | ./ip_filter > result.tst

diff ip_filter.tst result.tst 
