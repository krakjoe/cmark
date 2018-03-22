--TEST--
CommonMark\Node\Heading construct with level
--FILE--
<?php
$heading = new CommonMark\Node\Heading(3);

var_dump($heading->level);
?>
--EXPECT--
int(3)
