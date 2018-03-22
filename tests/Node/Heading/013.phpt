--TEST--
CommonMark\Node\Heading isset level
--FILE--
<?php
$heading = new CommonMark\Node\Heading;

$f = function() use($heading) {
	return isset($heading->level);
};

var_dump($heading->level);
var_dump($f());

$heading->level = 3;

var_dump($heading->level);
var_dump($f());
?>
--EXPECT--
int(1)
bool(true)
int(3)
bool(true)
