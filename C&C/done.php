<?php
if(!isset($_GET['id']))die;
$bot_id = $_GET['id'];

$mysqli = new mysqli('localhost','root','','xbot');

$query = "DELETE FROM bots_commands WHERE `ID` = '".$bot_id."'";

$mysqli->query($query);


?>