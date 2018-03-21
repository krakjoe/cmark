--TEST--
CommonMark\Node\BulletList cached read tight
--FILE--
<?php
$list = new CommonMark\Node\BulletList(true);

$f = function() use($list) {
	return $list->tight;
};

var_dump($f(), $f());
?>
--EXPECT--
bool(true)
bool(true)
