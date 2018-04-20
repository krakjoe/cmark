--TEST--
CommonMark\CQL compile error
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
[link1](here1)
[link2](here2)
EOD
);

$call = new \CommonMark\CQL(<<<EOD
/firstChild/[]
EOD
);
?>
--EXPECTF--
Fatal error: Uncaught RuntimeException: failed to compile call near character 13 "[]" in %s:9
Stack trace:
#0 %s(9): CommonMark\CQL->__construct('/firstChild/[]')
#1 {main}
  thrown in %s on line 9
