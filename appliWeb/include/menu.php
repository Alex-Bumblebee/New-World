<!--Navbar-->
    <nav class="navbar navbar-toggleable-md navbar-dark bg-primary">
        <div class="container">
            <button class="navbar-toggler navbar-toggler-right" type="button" data-toggle="collapse" data-target="#navbarNav1" aria-controls="navbarNav1" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <a class="navbar-brand" href="index.php">
                <strong>NW</strong>
            </a>
            <div class="collapse navbar-collapse" id="navbarNav1">
                <ul class="navbar-nav mr-auto">
                    <li class="nav-item <?php if(isset($page_en_cours) AND $page_en_cours == "accueil"){ echo 'active';} ?>" >
                        <a class="nav-link" href="index.php">Accueil </a>
                    </li>
                    <li class="nav-item <?php if(isset($page_en_cours) AND $page_en_cours == "acheter"){ echo 'active';} ?>">
                        <a class="nav-link" href="acheter.php">Acheter </a>
                    </li>
                    <li class="nav-item <?php if(isset($page_en_cours) AND $page_en_cours == "produire"){ echo 'active';} ?>" >
                        <a class="nav-link" href="produire.php">Produire </a>
                    </li>
                    <li class="nav-item <?php if(isset($page_en_cours) AND $page_en_cours == "distribuer"){ echo 'active';} ?>" >
                        <a class="nav-link" href="distribuer.php">Distribuer </a>
                    </li>
                </ul>
            </div>
            <div class="collapse navbar-collapse" id="navbarNav3">
                <ul class="navbar-nav ml-auto">
                    <li class="nav-item">
                        <a class="nav-link waves-effect waves-light" href="panier.php"><i class="fa fa-shopping-cart"></i> Panier | <?php echo TotalLot(); ?></a>
                    </li>
                    <?php if (!isset($_SESSION['nw']['compte']['ok'])) { 
                    ?>
                    <li class="nav-item">
                        <a class="nav-link waves-effect waves-light" href="connexion.php"><i class="fa fa-sign-in"></i> Connexion</a>
                    </li>
                    <?php } ?>
                    <?php if (isset($_SESSION['nw']['compte']['ok'])) {
                    ?>
                    <li class="nav-item btn-group">
                    <a class="nav-link dropdown-toggle" id="dropdownMenu1" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i class="fa fa-user"></i> Profil</a>
                    <div class="dropdown-menu" aria-labelledby="dropdownMenu1">
                        <a class="dropdown-item" href="parametres.php"> <i class="fa fa-cog" aria-hidden="true"></i> Paramètres</a>
                        <hr>
                        <a class="dropdown-item" href="deconnexion.php"> <i class="fa fa-power-off" aria-hidden="true"></i> Deconnexion</a>
                    </div>
                    <?php } ?>
                </li>
                </ul>
            </div>
        </div>
    </nav>
<!--/.Navbar-->