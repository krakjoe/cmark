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
/children(Paragraph)/children
EOD
);
?>
--EXPECTF--
Fatal error: Uncaught RuntimeException: failed to compile call near character 21 "/children" in %s:9
Stack trace:
#0 %s(9): CommonMark\CQL->__construct('/children(Parag...')
#1 {main}
  thrown in %s on line 9
