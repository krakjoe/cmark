--TEST--
CommonMark\Node\Heading cached read
--FILE--
<?php
$heading = new CommonMark\Node\Heading();
$heading->level = 3;

$f = function() use($heading) {
	return $heading->level;
};

var_dump($f());
var_dump($f());
?>
--EXPECT--
int(3)
int(3)
