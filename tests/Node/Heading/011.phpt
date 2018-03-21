--TEST--
CommonMark\Node\Heading isset
--FILE--
<?php
$heading = new CommonMark\Node\Heading();

var_dump($heading->level);

var_dump(isset($heading->level));

$heading->level = 2;

var_dump($heading->level);

var_dump(isset($heading->level));
?>
--EXPECT--
int(1)
bool(true)
int(2)
bool(true)
