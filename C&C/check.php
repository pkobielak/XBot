<?php
if(!isset($_GET['id']))die;
$bot_id=$_GET['id'];

$mysqli = new mysqli('localhost','root','','xbot');
$query = "SELECT `COMMAND` FROM `bots_commands` WHERE `ID`='".$bot_id."'";
$result = $mysqli->query($query);
$row = mysqli_fetch_assoc($result);

echo $row['COMMAND'];

?>