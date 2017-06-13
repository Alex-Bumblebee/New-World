<?php 
    require_once("./include/database.php");
    require_once("./include/functions.php");
    $page_en_cours = "confirmation";
    session_start();
    if (isset($_GET['pseudo'],$_GET['key']) AND !empty($_GET['pseudo']) AND !empty($_GET['key'])) {
        $pseudo = htmlspecialchars(urldecode($_GET['pseudo']));
        $key = htmlspecialchars($_GET['key']);
        $requser = $bdd->prepare("SELECT * FROM utilisateur WHERE pseudo = ? AND cle = ?");
        $requser->execute(array($pseudo,$key));
        $utilisateur_existe = $requser->rowCount();

        if ($utilisateur_existe == 1) {
            $user = $requser->fetch();
            if ($user['verifie'] == 0) {
                $maj_user = $bdd->prepare("UPDATE utilisateur SET verifie = 1 WHERE pseudo = ? AND cle = ?");
                $maj_user->execute(array($pseudo,$key));
                $_SESSION['nw']['success'] = "Votre compte à été vérifié !";
                header('Location: connexion.php');
                $ok = "Votre compte à bien été confirmé";
            } elseif($user['verifie'] == 1) {
                $_SESSION['nw']['warning'] = "Votre compte est déjà confirmé !";
                header('Location: connexion.php');
            } else {
                $_SESSION['nw']['error'] = "Erreur de confirmation !";
                header('Location: connexion.php');
            }
        } else {
            $_SESSION['nw']['error'] = "L'utilisateur n'existe pas ou ne correspond pas !";
            header('Location: connexion.php');
        }
    }
 ?>