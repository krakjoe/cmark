--TEST--
CommonMark\Node\Heading cached write
--FILE--
<?php
$heading = new CommonMark\Node\Heading();

$f = function($value) use($heading) {
	return $heading->level = $value;
};

var_dump($f(1));
var_dump($f(2));
?>
--EXPECT--
int(1)
int(2)
