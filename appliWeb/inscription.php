<?php 
    require_once("./include/database.php");
    require_once("./include/functions.php");
    $page_en_cours = "inscription";
    $req_questionsecurite = $bdd->prepare("SELECT * FROM question");
    $req_questionsecurite->execute();
    $req_typeuser = $bdd->prepare("SELECT * FROM typeUtilisateur");
    $req_typeuser->execute();

    if (isset($_POST['submit_inscription'])) {
        if(isset($_POST['pseudo_inscription'],$_POST['mdp1_inscription'],$_POST['mdp2_inscription'],$_POST['mail_inscription'],$_POST['nom_inscription'],$_POST['prenom_inscription'],$_POST['tel_inscription'],$_POST['adresse1_inscription'],$_POST['codepostal_inscription'],$_POST['ville_inscription'],$_POST['typecompte_inscription'],$_POST['questionsecurite_inscription'],$_POST['questionreponse_inscription']) AND !empty($_POST['pseudo_inscription']) AND !empty($_POST['mdp1_inscription']) AND !empty($_POST['mdp2_inscription']) AND !empty($_POST['mail_inscription']) AND !empty($_POST['nom_inscription']) AND !empty($_POST['prenom_inscription']) AND !empty($_POST['tel_inscription']) AND !empty($_POST['adresse1_inscription']) AND !empty($_POST['codepostal_inscription']) AND !empty($_POST['ville_inscription']) AND !empty($_POST['typecompte_inscription']) AND !empty($_POST['questionsecurite_inscription']) AND !empty($_POST['questionreponse_inscription'])){
                $pseudo_inscription = htmlspecialchars($_POST['pseudo_inscription']);
                $mdp1_inscription = htmlspecialchars($_POST['mdp1_inscription']);
                $mdp2_inscription = htmlspecialchars($_POST['mdp2_inscription']);
                $mail_inscription = htmlspecialchars($_POST['mail_inscription']);
                $nom_inscription = htmlspecialchars($_POST['nom_inscription']);
                $prenom_inscription = htmlspecialchars($_POST['prenom_inscription']);
                $tel_inscription = htmlspecialchars($_POST['tel_inscription']);
                $adresse1_inscription = htmlspecialchars($_POST['adresse1_inscription']);
                $codepostal_inscription = htmlspecialchars($_POST['codepostal_inscription']);
                $ville_inscription = htmlspecialchars($_POST['ville_inscription']);
                $typecompte_inscription = htmlspecialchars($_POST['typecompte_inscription']);
                $questionsecurite_inscription = htmlspecialchars($_POST['questionsecurite_inscription']);
                $questionreponse_inscription = htmlspecialchars($_POST['questionreponse_inscription']);
                $mdp = password_hash($mdp1_inscription,PASSWORD_BCRYPT);
                $mdp2 = password_hash($mdp2_inscription,PASSWORD_BCRYPT);
                $pseudolenght = strlen($pseudo_inscription);
                if ($pseudolenght <= 255 AND preg_match('/^[A-Za-z0-9_]+$/', $pseudo_inscription)) {
                    $requete_pseudo = $bdd->prepare("SELECT identifiant FROM utilisateur WHERE pseudo = ?");
                    $requete_pseudo->execute(array($pseudo_inscription));
                    $existe_pseudo = $requete_pseudo->rowCount();
                    if ($existe_pseudo == 0) {
                        if (filter_var($mail_inscription, FILTER_VALIDATE_EMAIL)) {
                            $requete_mail = $bdd->prepare("SELECT identifiant FROM utilisateur WHERE email = ?");
                            $requete_mail->execute(array($mail_inscription));
                            $existe_mail = $requete_mail->rowCount();
                            if ($existe_mail == 0) {
                                if ($mdp1_inscription == $mdp2_inscription) {
                                    $longueur_cle = 15;
                                    $cle = "";
                                    for ($i=1; $i < $longueur_cle; $i++) { 
                                        $cle .= mt_rand(0,9);
                                    }
                                    $requete_nombre = $bdd->prepare("SELECT identifiant FROM utilisateur ORDER BY identifiant DESC LIMIT 1");
                                    $requete_nombre->execute();
                                    $nombre_user = $requete_nombre->fetch();
                                    if ($nombre_user['identifiant'] == null) {
                                        $id_user = 1;
                                    } else {
                                        $id_user = $nombre_user['identifiant'] + 1;
                                    }
                                    $requete_insertion = $bdd->prepare("INSERT INTO utilisateur(`identifiant`, `prenom`, `nom`, `adresse1`, `ville`, `email`, `telephone`, `codePostal`, `cle`, `motDePasse`, `pseudo`, `pays`, `id_Question`, `id_typeUtilisateur`, `reponsequestion`,`dateInscription`) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NOW())");
                                    $requete_insertion->execute(array($id_user,$prenom_inscription,$nom_inscription,$adresse1_inscription,$ville_inscription,$mail_inscription,$tel_inscription,$codepostal_inscription,$cle,$mdp,$pseudo_inscription,"France",$questionsecurite_inscription,$typecompte_inscription, $questionreponse_inscription));
                                    $header = "MIME-Version: 1.0\r\n";
                                    $header .= 'From: "NewWorld Support" <support@newworld.com>'."\n";
                                    $header .= 'Content-Type:text/html; charset="utf-8"'."\n";
                                    $header .=  'Content-Transfer-Encoding: 8 bits';
                                    $to = "alexbourdon13@gmail.com"; 
                                    $subject = 'Confirmation de compte NewWorld';
                                    $body = '
                                    <html>
                                        <body>
                                            <div align="center">
                                                <a href="http://localhost/NW2/confirmation.php?pseudo='.urlencode($pseudo_inscription).'&key='.$cle.'">Confirmer votre comtpe</a>
                                            </div>
                                        <body>
                                    <html>
                                        ';
                                    if (mail($to, $subject, $body, $header)) {
                                        $_SESSION['nw']['success'] = "Votre compte à été créer !";
                                        header('Location: connexion.php');
                                    }
                                } else {
                                    $erreur = "Les mots de passes ne correspondent pas !";
                                }
                            } else {
                                $erreur = "Ce mail est déjà utilisé !";
                            }
                        } else {
                            $erreur = "Votre mail n'est pas valide !";                        
                        }
                    } else {
                        $erreur = "Votre pseudo existe déjà !";
                    }
                } else {
                    $erreur = "Votre pseudo n'est pas valide !";
                }
        } else {
            $erreur = "Veuillez remplir tous les champs !"; 
        }
    }

    require_once("./view/inscription.view.php");
 ?>