<?php
	require_once("./include/database.php");
    require_once("./include/functions.php");
    $page_en_cours = "parametres";
	session_start();
	if (isset($_SESSION['nw']['success']) AND (!empty($_SESSION['nw']['success']))){
		$success = $_SESSION['nw']['success'];
		unset($_SESSION['nw']['success']);
	}
	if (isset($_SESSION['nw']['error']) AND (!empty($_SESSION['nw']['error']))){
		$error = $_SESSION['nw']['error'];
		unset($_SESSION['nw']['error']);
	}
	if (isset($_SESSION['nw']['warning']) AND (!empty($_SESSION['nw']['warning']))){
		$warning = $_SESSION['nw']['warning'];
		unset($_SESSION['nw']['warning']);
	}
	if (!isset($_SESSION['nw']['compte']['ok'])){
		header('Location: index.php');
	}

    require_once("./view/parametres.view.php");
 ?>