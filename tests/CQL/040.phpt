--TEST--
CommonMark\CQL compile error
--FILE--
<?php
$call = new \CommonMark\CQL(<<<EOD
/firstChild(*)
EOD
);
?>
--EXPECTF--
Fatal error: Uncaught RuntimeException: failed to compile call near character 13 "*)" in %s:3
Stack trace:
#0 %s(3): CommonMark\CQL->__construct('/firstChild(*)')
#1 {main}
  thrown in %s on line 3
