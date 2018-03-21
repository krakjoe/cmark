--TEST--
CommonMark\Node\BulletList cached write tight
--FILE--
<?php
$list = new CommonMark\Node\BulletList(true);

$f = function($val) use($list) {
	return $list->tight = $val;
};

var_dump($f(false), $f(true));
?>
--EXPECT--
bool(false)
bool(true)
