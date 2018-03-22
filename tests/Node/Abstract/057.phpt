--TEST--
CommonMark\Node isset endColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$title = $doc->firstChild;

$f = function() use($title) {
	return isset($title->endColumn);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
