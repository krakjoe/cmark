--TEST--
CommonMark\Node cached read firstChild
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$f = function() use($doc) {
	return $doc->firstChild;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
