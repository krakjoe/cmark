--TEST--
CommonMark\Node cached read parent
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$f = function() use($doc) {
	return $doc->firstChild->parent;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
