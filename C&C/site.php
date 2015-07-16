<center>
<?php

echo "<br><br>XBOT ALPHA<br><br><br>";

mysql_connect('localhost','root','');
mysql_select_db('xbot');

$res=mysql_query("SELECT * FROM bots_info ORDER BY LAST_SEEN DESC");

echo '<table border="1">ALL BOTS';
echo '<tr> <td><center>ID</center></td> <td><center>Version</center></td> <td><center>IP</center></td> <td><center>OS</center></td> <td><center>CPU</center></td> <td><center>Status</center></td> </tr>';
while($row=mysql_fetch_assoc($res))
{
	if(time()-strtotime($row['LAST_SEEN'])<315)
	$status='<span style="color:green">Online</span>';// ".(time()-strtotime($row['LAST_SEEN']));
	else
	$status='<span style="color:red">Offline</span>';// ".(time()-strtotime($row['LAST_SEEN']));
	echo "<tr> <td>".$row['ID']."</td> <td>".$row['VERSION']."</td> <td>".$row['IP']."</td> <td>".$row['OS']."</td> <td>".$row['CPU']."</td> <td>".$status."</td> </tr>";
}
echo '</table><br><br>';

?>
</center>

<?php // php for automatic refresh
$page = $_SERVER['PHP_SELF'];
$sec = 5;
?>
<head>
<meta http-equiv="refresh" content="<?php echo $sec ?>;URL=<?php echo $page?>">
</head>

