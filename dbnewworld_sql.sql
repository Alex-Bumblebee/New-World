-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Mar 13 Juin 2017 à 06:30
-- Version du serveur :  5.5.55-0+deb8u1
-- Version de PHP :  5.6.30-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `dbnewworld`
--

-- --------------------------------------------------------

--
-- Structure de la table `categorie`
--

CREATE TABLE IF NOT EXISTS `categorie` (
  `no_categorie` varchar(11) NOT NULL DEFAULT '',
  `libelle` varchar(30) DEFAULT NULL,
  `no_rayon` varchar(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `categorie`
--

INSERT INTO `categorie` (`no_categorie`, `libelle`, `no_rayon`) VALUES
('1', 'Catégorie test', '1'),
('2', 'Fruit', '2'),
('3', 'Légume', '2'),
('4', 'Test2', '1');

-- --------------------------------------------------------

--
-- Structure de la table `controleproducteur`
--

CREATE TABLE IF NOT EXISTS `controleproducteur` (
  `visiteConcluante` tinyint(1) DEFAULT NULL,
  `motifRejet` varchar(250) DEFAULT NULL,
  `heureDebutControle` time DEFAULT NULL,
  `etat` tinyint(4) NOT NULL DEFAULT '0',
  `numerovisite` int(11) NOT NULL,
  `identifiant` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `controleproducteur`
--

INSERT INTO `controleproducteur` (`visiteConcluante`, `motifRejet`, `heureDebutControle`, `etat`, `numerovisite`, `identifiant`) VALUES
(1, 'De', '00:00:00', 1, 5, 2),
(1, 'De', '00:00:00', 1, 6, 2);

-- --------------------------------------------------------

--
-- Structure de la table `localite`
--

CREATE TABLE IF NOT EXISTS `localite` (
  `noInsee` varchar(10) NOT NULL DEFAULT '',
  `nom` varchar(50) DEFAULT NULL,
  `codePostal` varchar(10) DEFAULT NULL,
  `acheminement` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `lot`
--

CREATE TABLE IF NOT EXISTS `lot` (
  `nolot` int(11) NOT NULL DEFAULT '0',
  `quantiteLot` float DEFAULT '1',
  `quantiteProduit` float NOT NULL,
  `description` varchar(120) NOT NULL DEFAULT 'Aucune description',
  `dateRecolte` date DEFAULT NULL,
  `nbJourConservation` int(11) DEFAULT NULL,
  `uniteDeVente` varchar(50) DEFAULT '€',
  `modeProduction` varchar(25) DEFAULT NULL,
  `ramassageManuel` tinyint(1) DEFAULT NULL,
  `prixUnitaire` float DEFAULT NULL,
  `numero` int(11) NOT NULL,
  `identifiant` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `lot`
--

INSERT INTO `lot` (`nolot`, `quantiteLot`, `quantiteProduit`, `description`, `dateRecolte`, `nbJourConservation`, `uniteDeVente`, `modeProduction`, `ramassageManuel`, `prixUnitaire`, `numero`, `identifiant`) VALUES
(4, 1, 10, 'Aucune description', '2017-06-12', 5, '€', 'Industriel', 1, 5, 1, 5),
(1, 20, 20, 'Aucune description', '2017-06-08', 20, '€', 'Industriel', 1, 2, 2, 5),
(3, 12, 12, 'Vous pourrez faire des bonnes soupes !', '2017-06-15', 10, '€', 'Industriel', 1, 5, 3, 5),
(5, 1, 10, 'de', '2017-06-12', 5, '€', 'dede', 1, 5, 3, 5);

-- --------------------------------------------------------

--
-- Structure de la table `Personnel`
--

CREATE TABLE IF NOT EXISTS `Personnel` (
  `numeroPersonnel` int(11) NOT NULL DEFAULT '0',
  `username` varchar(60) NOT NULL,
  `nom` varchar(25) DEFAULT NULL,
  `prenom` varchar(25) DEFAULT NULL,
  `email` varchar(35) DEFAULT NULL,
  `typePersonnel` varchar(25) DEFAULT NULL,
  `ssNumber` varchar(30) DEFAULT NULL,
  `mdp` varchar(60) DEFAULT NULL,
  `date_Embauche` date DEFAULT NULL,
  `tel_fixe` varchar(12) NOT NULL,
  `tel_portable` varchar(12) NOT NULL,
  `valide` tinyint(4) NOT NULL,
  `adresse` varchar(100) NOT NULL,
  `iban` varchar(50) NOT NULL,
  `code_postal` varchar(7) NOT NULL,
  `ville` varchar(60) NOT NULL,
  `supprime` tinyint(1) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `Personnel`
--

INSERT INTO `Personnel` (`numeroPersonnel`, `username`, `nom`, `prenom`, `email`, `typePersonnel`, `ssNumber`, `mdp`, `date_Embauche`, `tel_fixe`, `tel_portable`, `valide`, `adresse`, `iban`, `code_postal`, `ville`, `supprime`) VALUES
(0, 'alex.bourdon', 'BOURDON', 'Ale', 'alexbourdon13@gmail.com', '', NULL, 'C05SJCGm1nIL', '2017-06-08', '03863222071', '0631024413', 1, '15 rue abanel', 'JDEHBF55252DE', '05000', 'GAP', 1),
(1, 'alex.bourdon', 'BOURDON', 'Alex', 'alexbourdon13@gmail.com', 'Gestionnaire', 'NUMDE5', '130797', '2017-05-29', '03863222071', '0631024413', 1, '15 rue abanel', 'JDEHBF55252DE', '05000', 'GAP', 0),
(2, 'alex.bourdo', 'BOURDO', 'Ale', 'alexbourdon13@gmail.co', 'Controleur', NULL, '130797', '2017-06-13', '0386322207', '063102441', 1, '15 rue abane', 'JDEHBF55252DE', '0500', 'GA', 1);

-- --------------------------------------------------------

--
-- Structure de la table `pointdevente`
--

CREATE TABLE IF NOT EXISTS `pointdevente` (
  `no_pdv` varchar(11) NOT NULL DEFAULT '',
  `adresse` varchar(50) DEFAULT NULL,
  `codePostal` varchar(10) DEFAULT NULL,
  `nom` varchar(50) DEFAULT NULL,
  `activite` varchar(50) DEFAULT NULL,
  `ville` varchar(30) DEFAULT NULL,
  `tel` varchar(20) DEFAULT NULL,
  `responsable` int(11) DEFAULT NULL,
  `valide` tinyint(4) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `pointdevente`
--

INSERT INTO `pointdevente` (`no_pdv`, `adresse`, `codePostal`, `nom`, `activite`, `ville`, `tel`, `responsable`, `valide`) VALUES
('1', '15 rue aubanel', '05000', 'Test', 'Fruit', 'GAP', '0631024413', 5, 0),
('2', 'test', 'test', 'Test', 'de', 'Ok', '063102', 6, 0),
('3', 'TEst', 'TEst', 'TEst', 'TEst', 'TEst', '06', 6, 1);

-- --------------------------------------------------------

--
-- Structure de la table `produit`
--

CREATE TABLE IF NOT EXISTS `produit` (
  `numero` int(11) NOT NULL DEFAULT '0',
  `libelle` varchar(100) DEFAULT NULL,
  `no_categorie` varchar(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `produit`
--

INSERT INTO `produit` (`numero`, `libelle`, `no_categorie`) VALUES
(1, 'Produit Test', '1'),
(2, 'Pommes', '2'),
(3, 'Carottes', '3');

-- --------------------------------------------------------

--
-- Structure de la table `proposera`
--

CREATE TABLE IF NOT EXISTS `proposera` (
  `no_pdv` varchar(11) NOT NULL,
  `numero` int(11) NOT NULL,
  `identifiant` int(11) NOT NULL,
  `nolot` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `question`
--

CREATE TABLE IF NOT EXISTS `question` (
  `id_Question` int(11) NOT NULL DEFAULT '0',
  `libelleQuestion` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `question`
--

INSERT INTO `question` (`id_Question`, `libelleQuestion`) VALUES
(1, 'Quelle est votre ville de naissance ?'),
(2, 'Quelle est votre couleur préférée ?'),
(3, 'Quelle était le nom de votre école primaire ?');

-- --------------------------------------------------------

--
-- Structure de la table `rayon`
--

CREATE TABLE IF NOT EXISTS `rayon` (
  `no_rayon` varchar(11) NOT NULL,
  `libelle` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `rayon`
--

INSERT INTO `rayon` (`no_rayon`, `libelle`) VALUES
('1', 'Rayon test'),
('2', 'Fruits et légumes');

-- --------------------------------------------------------

--
-- Structure de la table `typeutilisateur`
--

CREATE TABLE IF NOT EXISTS `typeutilisateur` (
  `id_typeUtilisateur` int(11) NOT NULL DEFAULT '0',
  `typeUtilisateur` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `typeutilisateur`
--

INSERT INTO `typeutilisateur` (`id_typeUtilisateur`, `typeUtilisateur`) VALUES
(1, 'Client'),
(2, 'Vendeur'),
(3, 'Client et Vendeur'),
(4, 'Point de vente');

-- --------------------------------------------------------

--
-- Structure de la table `utilisateur`
--

CREATE TABLE IF NOT EXISTS `utilisateur` (
  `identifiant` int(11) NOT NULL DEFAULT '0',
  `prenom` varchar(25) DEFAULT NULL,
  `nom` varchar(40) DEFAULT NULL,
  `dateNaissance` date DEFAULT NULL,
  `adresse1` varchar(75) DEFAULT NULL,
  `adresse2` varchar(75) DEFAULT NULL,
  `ville` varchar(25) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `telephone` varchar(15) DEFAULT NULL,
  `codePostal` varchar(10) DEFAULT NULL,
  `cle` varchar(100) DEFAULT NULL,
  `motDePasse` varchar(100) DEFAULT NULL,
  `dateInscription` datetime DEFAULT NULL,
  `verifie` tinyint(1) DEFAULT '0',
  `pseudo` varchar(40) DEFAULT NULL,
  `pays` varchar(50) DEFAULT NULL,
  `idFacebook` varchar(100) DEFAULT NULL,
  `idTwitter` varchar(100) DEFAULT NULL,
  `idGoogle` varchar(100) DEFAULT NULL,
  `id_Question` int(11) NOT NULL,
  `id_typeUtilisateur` int(11) NOT NULL,
  `reponsequestion` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `utilisateur`
--

INSERT INTO `utilisateur` (`identifiant`, `prenom`, `nom`, `dateNaissance`, `adresse1`, `adresse2`, `ville`, `email`, `telephone`, `codePostal`, `cle`, `motDePasse`, `dateInscription`, `verifie`, `pseudo`, `pays`, `idFacebook`, `idTwitter`, `idGoogle`, `id_Question`, `id_typeUtilisateur`, `reponsequestion`) VALUES
(1, 'td', 'td', NULL, 'E', NULL, 't', 't@t.tdd', '0631024413', '06310', '49032826794494', '$2y$10$Q1N9TSj4SzrfnIBTbXhNlewnbH7oJV14p4fbdXB66kXfea0OKvgiK', '2017-06-05 03:22:13', 1, 'tdd', 'France', NULL, NULL, NULL, 1, 1, 'de'),
(2, 'td', 'td', NULL, 'E', NULL, 't', 't@t.tddd', '0631024413', '06310', '23674371759508', '$2y$10$VRNCyqwz1MQAqv29Lmn.e.n3cLepvI5ZrwETr0NlAxXdRvk4DhP3C', '2017-06-05 03:43:51', 0, 'tddd', 'France', NULL, NULL, NULL, 1, 1, 'de'),
(3, 'd', 'd', NULL, 'd', NULL, '1', 'de@e.fr', '063102', '02', '39260052161624', '$2y$10$X7cwWp1dYQpuj.fyPT8MhO6Relm43wPln2rkR7tmc28tD4l9opS7W', '2017-06-05 03:51:58', 1, 'dedede', 'France', NULL, NULL, NULL, 1, 1, '1'),
(4, 'd', 'd', NULL, 'd', NULL, '1', 'de@e.frd', '063102', '02', '42374316492497', '$2y$10$DJqT/UEK.iRfF584TWeTneEk0vcvh9mFiOqB3ljzD4wAIE51SRpkO', '2017-06-05 04:12:21', 1, 'dededed', 'France', NULL, NULL, NULL, 1, 1, '1'),
(5, 'Test', 'Test', NULL, '13 rue', NULL, 'TEST', 'test@fr.fr', '3630', '05000', '87883036750263', '$2y$10$.T4A2fByXkKB7UsGWciRQ.7zwE7xxCgJocEeXuJtGKW.tb0NyHN.a', '2017-06-05 04:44:27', 1, 'Test', 'France', NULL, NULL, NULL, 1, 3, 'Test'),
(6, 'pdv', 'pdv', NULL, 'pdv', NULL, 'pdv', 'pdv@pdv.pdv', 'pdv', 'pdv', '59441518373247', '$2y$10$T7ObC/KSB2no.2QZ0LRIKOIPu210UlBCTSdXiX7Z5iGrwzIG3ISjO', '2017-06-12 17:27:56', 1, 'PDV', 'France', NULL, NULL, NULL, 1, 4, 'pdv');

-- --------------------------------------------------------

--
-- Structure de la table `visite`
--

CREATE TABLE IF NOT EXISTS `visite` (
  `numerovisite` int(11) NOT NULL DEFAULT '0',
  `libellevisite` varchar(25) DEFAULT NULL,
  `dateVisite` date DEFAULT NULL,
  `identifiant` int(11) DEFAULT NULL,
  `Planificateur` int(11) DEFAULT NULL,
  `Controleur` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `visite`
--

INSERT INTO `visite` (`numerovisite`, `libellevisite`, `dateVisite`, `identifiant`, `Planificateur`, `Controleur`) VALUES
(1, 'Test', '2013-06-17', NULL, NULL, 2),
(4, 'Test', '0000-00-00', 2017, NULL, 2),
(5, 'Test', '0000-00-00', 2017, NULL, 2),
(6, 'Test', '0000-00-00', 2017, NULL, 2);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `categorie`
--
ALTER TABLE `categorie`
 ADD PRIMARY KEY (`no_categorie`), ADD KEY `no_rayon` (`no_rayon`);

--
-- Index pour la table `controleproducteur`
--
ALTER TABLE `controleproducteur`
 ADD PRIMARY KEY (`numerovisite`,`identifiant`), ADD KEY `identifiant` (`identifiant`);

--
-- Index pour la table `localite`
--
ALTER TABLE `localite`
 ADD PRIMARY KEY (`noInsee`);

--
-- Index pour la table `lot`
--
ALTER TABLE `lot`
 ADD PRIMARY KEY (`numero`,`identifiant`,`nolot`), ADD KEY `identifiant` (`identifiant`);

--
-- Index pour la table `Personnel`
--
ALTER TABLE `Personnel`
 ADD PRIMARY KEY (`numeroPersonnel`);

--
-- Index pour la table `pointdevente`
--
ALTER TABLE `pointdevente`
 ADD PRIMARY KEY (`no_pdv`);

--
-- Index pour la table `produit`
--
ALTER TABLE `produit`
 ADD PRIMARY KEY (`numero`), ADD KEY `no_categorie` (`no_categorie`);

--
-- Index pour la table `proposera`
--
ALTER TABLE `proposera`
 ADD PRIMARY KEY (`no_pdv`,`numero`,`identifiant`,`nolot`), ADD KEY `numero` (`numero`,`identifiant`,`nolot`);

--
-- Index pour la table `question`
--
ALTER TABLE `question`
 ADD PRIMARY KEY (`id_Question`);

--
-- Index pour la table `rayon`
--
ALTER TABLE `rayon`
 ADD PRIMARY KEY (`no_rayon`);

--
-- Index pour la table `typeutilisateur`
--
ALTER TABLE `typeutilisateur`
 ADD PRIMARY KEY (`id_typeUtilisateur`);

--
-- Index pour la table `utilisateur`
--
ALTER TABLE `utilisateur`
 ADD PRIMARY KEY (`identifiant`), ADD KEY `id_Question` (`id_Question`), ADD KEY `id_typeUtilisateur` (`id_typeUtilisateur`);

--
-- Index pour la table `visite`
--
ALTER TABLE `visite`
 ADD PRIMARY KEY (`numerovisite`), ADD KEY `Planificateur` (`Planificateur`), ADD KEY `Contrôleur` (`Controleur`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
