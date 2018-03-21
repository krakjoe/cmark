--TEST--
CommonMark\Node\BulletList cached write delimiter
--FILE--
<?php
$list = new CommonMark\Node\BulletList();

$f = function($val) use($list) {
	return $list->delimiter = $val;
};

var_dump($f(CommonMark\Node\Lists\Delimit\Period), $f(CommonMark\Node\Lists\Delimit\Paren));
?>
--EXPECT--
int(1)
int(2)
