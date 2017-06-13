<?php 
session_start();
$_SESSION['nw']['compte'] = array();
unset($_SESSION['nw']['compte']);
header("Location: index.php");
?>