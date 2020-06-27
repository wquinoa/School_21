<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //

/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** MySQL database username */
define( 'DB_USER', 'root' );

/** MySQL database password */
define( 'DB_PASSWORD', '' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/** File system method */
define('FS_METHOD', 'direct');

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         ']VoF%,:@OD-Rx:3k#aIq&=~n?G.P^(2pr/7Yv?,8|IR/&j]+UL));XUT})1$WGi`' );
define( 'SECURE_AUTH_KEY',  'dUnkuTR|^iX:~Pq>hIDmYH#HPZtW&mUt??Qf^r{!>0^W:)|MEoGG>H>?(p+iNfpl' );
define( 'LOGGED_IN_KEY',    'wWp;<H=+6<w8X|TtYbmqH2=j@ua+=V[RpbPF+|t*}Fe)zGeCfpU+9UrC_j49w<|d' );
define( 'NONCE_KEY',        'lHffS<CvsF}0?_4:xGhjc4wG+S`~ H=Re6V-+.ky6)+}~=r_QwXXg^HdNL)C aj7' );
define( 'AUTH_SALT',        'C.Wj%f@{@@lY,?xUFes@?@4[L|@AH,;7bB)8WG4-2n8|VZ|-[C7RcoVoc%kdZ9~t' );
define( 'SECURE_AUTH_SALT', 'D=b1.AG8.&$dwme@C|&Z->||Bd3j!X9`sA#7o1dgMC3>By=x/Pzy;|%+44k Y<eD' );
define( 'LOGGED_IN_SALT',   'SjgyB3r.K)WLn&<IC#If5 rpD!RezrtZX:>28-+H]&:B{rcFJ0>f0H:0#C*,`I%4' );
define( 'NONCE_SALT',       '7PbQ%yB6>O@>.+[iKd9}bP[=)y@zMFn2LRew8XR3p--V >EN~hpYH{7lEi|A*i@4' );

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
