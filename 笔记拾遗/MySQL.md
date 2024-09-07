# MONTH()

2024.09.07

业务：查询数据库中活动表中每个月有多少次活动。

活动有一个字段是start_time，表示活动开始时间，格式是：2024-09-05 00:00:00 这样的，要查出每个月的活动数量，那么需要知道每个活动的月份，可以使用mysql内置的MONTH函数来获得月份，然后分组查询即可：

```mysql
SELECT
	count( 0 ),
	MONTH ( start_time ) `month` 
FROM
	t_activity 
GROUP BY
	`month`
```

需要注意，如果列名跟字段名或函数名相同的话，可以使用 `` 符号括起来。